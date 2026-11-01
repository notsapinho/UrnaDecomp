// simulador::CWasmScreen and simulador::CWasmImageSurfaceOps, one object (src/units/69-uenux2-cwasmimagesurfaceops.mk
// says what shows it). No record names this file. The reconstruction's notes: which slots are written and which wait,
// and every name chosen, are in that fragment; the file-static helpers' names, their linkage and their split are chosen.
#include "cwasmscreen.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>

#include "api/gui/cmovie.h"
#include "api/gui/cstepsprogressbar.h"
#include "api/gui/iform.h"
#include "api/gui/itext.h"
#include "wasmjs.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp, whose generated declarations take an int for every pointer and
// size): the TPosition widths are what the bodies give, a 16-bit sign extension at the call
extern "C" {
void js_init(int width, int height);
void js_clear(const char* c);
void js_fill(int x, int y, int w, int h, const char* c);
void js_line(int x1, int y1, int x2, int y2, const char* c, int width);
void js_text(api::TPosition x, int y, api::TPosition maxw, const char* text, int size, int bold, int italic, const char* c,
             int align);
int js_measure_text_width(const char* text, int size, int bold, int italic);
void js_circle(int x, int y, int r, const char* c, int width);
void js_round_rect(int x, int y, api::TPosition w, api::TPosition h, int r, const char* c, int width);
void js_gray_gradient(int x, int y, api::TPosition w, api::TPosition h);
void js_image(const void* data, int size, int x, int y, api::TPosition w, api::TPosition h);
void js_path(int count, const int* types, const double* values, const char* c, int fill, int width);
void js_log(const char* msg);
}

namespace {

// the CSS colour of a TColor: the bodies index a table of 38 strings (1529596) and pass "#000000" above 37, which is
// what clang makes of a switch; 9104's fill reads a second table of entries 1 to 37 (1529448), the same switch where
// its caller has ruled out 0
const char* Cor(api::TColor cor)
{
    switch (static_cast<int>(cor)) {
    case 0: return "rgba(0,0,0,0)";
    case 1: return "#ffffff";
    case 2: return "#000000";
    case 3: return "#808080";
    case 4: return "#d3d3d3";
    case 5: return "#acacac";
    case 6: return "#404040";
    case 7: return "#333333";
    case 8: return "#ff0000";
    case 9: return "#f08080";
    case 10: return "#8b0000";
    case 11: return "#00ff00";
    case 12: return "#90ee90";
    case 13: return "#006400";
    case 14: return "#0000ff";
    case 15: return "#add8e6";
    case 16: return "#00008b";
    case 17: return "#ffff00";
    case 18: return "#ffffe0";
    case 19: return "#eb7f29";
    case 20: return "#ffd300";
    case 21: return "#ffbe2e";
    case 22: return "#dbe2ef";
    case 23: return "#d9e8f6";
    case 24: return "#2672de";
    case 25: return "#1a4480";
    case 26: return "#f7bbb1";
    case 27: return "#e52207";
    case 28: return "#8b0a03";
    case 29: return "#fef0c8";
    case 30: return "#ffbe2e";
    case 31: return "#c66900";
    case 32: return "#b4d0b9";
    case 33: return "#008817";
    case 34: return "#446443";
    case 35: return "#e6e6e6";
    case 36: return "#c9c9c9";
    case 37: return "#adadad";
    default: return "#000000";
    }
}

// a corner for DrawRect (fn 9205): through this helper its four calls are the target's; SPoint aggregates or named
// points in DrawRect's body are not (the fragment lists the forms)
api::SPoint Ponto(api::TPosition x, api::TPosition y)
{
    api::SPoint ponto;
    ponto.x = x;
    ponto.y = y;
    return ponto;
}

void Ancora(int& x, int& y, int largura, int altura, api::EAnchorPoint ancora)
{
    switch (ancora) {
    case api::ANCHOR_TOP_RIGHT:
        x -= largura;
        break;
    case api::ANCHOR_TOP_CENTER:
        x -= largura / 2;
        break;
    case api::ANCHOR_MIDDLE_LEFT:
        y -= altura / 2;
        break;
    case api::ANCHOR_MIDDLE_RIGHT:
        x -= largura;
        y -= altura / 2;
        break;
    case api::ANCHOR_CENTER:
        x -= largura / 2;
        y -= altura / 2;
        break;
    case api::ANCHOR_BOTTOM_LEFT:
        y -= altura;
        break;
    case api::ANCHOR_BOTTOM_RIGHT:
        x -= largura;
        y -= altura;
        break;
    case api::ANCHOR_BOTTOM_CENTER:
        x -= largura / 2;
        y -= altura;
        break;
    default:
        break;
    }
}

api::SRect Normaliza(api::TPosition esquerda, api::TPosition topo, api::TPosition direita, api::TPosition base)
{
    return api::SRect{std::min(esquerda, direita), std::min(topo, base), std::max(esquerda, direita), std::max(topo, base)};
}

api::SRect Retangulo(api::TPosition x, api::TPosition y, api::TPosition largura, api::TPosition altura)
{
    return Normaliza(x, y, x + largura - 1, y + altura - 1);
}

// the type js_path takes for a path command
int TipoCaminho(api::SPathCommand::EType tipo)
{
    switch (tipo) {
    case api::SPathCommand::LINE_TO: return 1;
    case api::SPathCommand::ARC: return 2;
    case api::SPathCommand::CLOSE: return 3;
    default: return 0;
    }
}

// a big-endian 16-bit number of an image's header
uint16_t Le16(const uint8_t* bytes)
{
    return static_cast<uint16_t>(bytes[0] << 8 | bytes[1]);
}

// the text's Latin-1 as UTF-8 for the canvas (fn 5098; GetTextWidth and DrawText into a rectangle call it)
std::string ParaUtf8(const std::string& texto)
{
    std::string saida;
    saida.reserve(texto.size() * 2);
    for (const unsigned char c : texto) {
        if (c < 0x80) {
            saida.push_back(c);
        } else {
            saida.push_back(0xC0 | (c >> 6));
            saida.push_back(c & 0xBF);
        }
    }
    return saida;
}

// an image's width and height from its GIF, PNG or JPEG header, 1 by 1 when none gives them (slot 12 of
// CWasmImageSurfaceOps, fn 3493, calls it)
api::SPoint TamanhoImagem(const std::vector<uint8_t>& dados)
{
    const uint8_t* bytes = dados.data();
    const size_t tamanho = dados.size();
    if (tamanho >= 10 && bytes[0] == 'G' && bytes[1] == 'I' && bytes[2] == 'F') {
        api::SPoint ponto;
        std::memcpy(&ponto, bytes + 6, sizeof(ponto));
        return ponto;
    }
    api::TPosition altura = 1;
    api::TPosition largura = 1;
    const uint8_t assinaturaPng[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};
    if (tamanho >= 24 && std::equal(assinaturaPng, assinaturaPng + 8, bytes)) {
        largura = Le16(bytes + 18);
        altura = Le16(bytes + 22);
    } else if (tamanho >= 4 && bytes[0] == 0xFF && bytes[1] == 0xD8) {
        size_t i = 2;
        while (i + 9 < tamanho) {
            if (bytes[i] != 0xFF) {
                ++i;
                continue;
            }
            if (i + 4 > tamanho) {
                break;
            }
            const uint8_t* segmento = bytes + i;
            const uint8_t marcador = segmento[1];
            if (marcador == 0xD9 || marcador == 0xDA) {
                break;
            }
            i += 2;
            const size_t comprimento = Le16(bytes + i);
            if (comprimento < 2) {
                break;
            }
            i += comprimento;
            if (i > tamanho) {
                break;
            }
            if ((marcador >= 0xC0 && marcador <= 0xC3) || (marcador >= 0xC5 && marcador <= 0xC7) ||
                (marcador >= 0xC9 && marcador <= 0xCB) || (marcador >= 0xCD && marcador <= 0xCF)) {
                largura = Le16(segmento + 7);
                altura = Le16(segmento + 5);
                break;
            }
        }
    }
    return api::SPoint{largura, altura};
}


} // namespace

namespace simulador {

api::SharedBytes CWasmImageSurfaceOps::Slot2(const api::IImage& imagem, int, int) const
{
    return std::make_shared<std::vector<uint8_t>>(imagem.GetData());
}

uint8_t* CWasmImageSurfaceOps::Slot3(const api::IImageSurfaceSource& fonte, int, int) const
{
    return fonte.GetBytes();
}

uint8_t* CWasmImageSurfaceOps::Slot4(uint8_t* const& bytes, int, int) const
{
    return bytes;
}

api::SharedBytes CWasmImageSurfaceOps::Slot5(const api::IImage& imagem, int) const
{
    return std::make_shared<std::vector<uint8_t>>(imagem.GetData());
}

uint8_t* CWasmImageSurfaceOps::Slot6(const api::IImageSurfaceSource& fonte, int) const
{
    return fonte.GetBytes();
}

uint8_t* CWasmImageSurfaceOps::Slot7(uint8_t* const& bytes, int) const
{
    return bytes;
}

uint8_t* CWasmImageSurfaceOps::CopyBytes(const std::vector<uint8_t>& dados) const
{
    uint8_t* copia = new uint8_t[dados.size()];
    std::copy(dados.begin(), dados.end(), copia);
    return copia;
}

api::SharedBytes CWasmImageSurfaceOps::Slot9(uint8_t* const&) const
{
    return std::make_shared<std::vector<uint8_t>>();
}

api::SharedBytes CWasmImageSurfaceOps::Slot10(const api::IImageSurfaceSource& fonte) const
{
    return Slot9(fonte.GetBytes());
}

void CWasmImageSurfaceOps::FreeBytes(uint8_t* bytes) const
{
    delete[] bytes;
}

api::SPoint CWasmImageSurfaceOps::ImageSize(const std::vector<uint8_t>& dados) const
{
    if (dados.empty()) {
        return api::SPoint{1, 1};
    }
    return TamanhoImagem(dados);
}

api::SRect CWasmImageSurfaceOps::ImageRect(api::TPosition largura, api::TPosition altura, const api::SPoint& posicao,
                                           api::EAnchorPoint ancora) const
{
    api::TPosition x = posicao.x;
    api::TPosition y = posicao.y;

    switch (ancora) {
    case api::ANCHOR_TOP_RIGHT:
        x -= largura;
        break;
    case api::ANCHOR_TOP_CENTER:
        x -= largura / 2;
        break;
    case api::ANCHOR_MIDDLE_LEFT:
        y -= altura / 2;
        break;
    case api::ANCHOR_MIDDLE_RIGHT:
        x -= largura;
        y -= altura / 2;
        break;
    case api::ANCHOR_CENTER:
        x -= largura / 2;
        y -= altura / 2;
        break;
    case api::ANCHOR_BOTTOM_LEFT:
        y -= altura;
        break;
    case api::ANCHOR_BOTTOM_RIGHT:
        x -= largura;
        y -= altura;
        break;
    case api::ANCHOR_BOTTOM_CENTER:
        x -= largura / 2;
        y -= altura;
        break;
    default:
        break;
    }

    const api::TPosition direita = x + largura;
    const api::TPosition base = y + altura;
    return api::SRect{std::min(x, direita), std::min(y, base), std::max(x, direita), std::max(y, base)};
}

CWasmScreen::CWasmScreen(api::TPosition largura, api::TPosition altura)
    : m_escalaX(largura / 640.0)
    , m_escalaY(altura / 480.0)
{
    js_init(largura, altura);
    Clear(static_cast<api::TColor>(1));
    const std::string mensagem = "CWasmScreen this=" + std::to_string(reinterpret_cast<size_t>(this));
    js_log(mensagem.c_str());
}

void CWasmScreen::GetFontMetrics(uint8_t& largura, uint8_t& altura, const api::SFont& font)
{
    largura = std::max<api::TPosition>(font.size / 2, 1);
    altura = font.size;
}

void CWasmScreen::GetFontMetrics(api::TPosition& largura, api::TPosition& altura, const api::SFont& font,
                                 const std::string& texto)
{
    largura = GetTextWidth(texto, font);
    altura = std::max<api::TPosition>(font.size, 1);
}

void CWasmScreen::Clear(api::TColor cor)
{
    js_log("Clear(full)");
    js_clear(Cor(cor));
}

void CWasmScreen::Clear(const api::SRect& rect, api::TColor cor)
{
    FillRect(rect, cor);
}

void CWasmScreen::FillRect(const api::SRect& rect, api::TColor cor)
{
    const int x1 = EscalaX(rect.left);
    const int y1 = EscalaY(rect.top);
    const int x2 = EscalaX(rect.right);
    const int y2 = EscalaY(rect.bottom);
    js_fill(std::min(x1, x2), std::min(y1, y2), std::abs(x1 - x2) + 1, std::abs(y1 - y2) + 1, Cor(cor));
}

void CWasmScreen::DrawPixel(const api::SPoint& ponto, api::TColor cor)
{
    js_fill(EscalaX(ponto.x), EscalaY(ponto.y), 1, 1, Cor(cor));
}

void CWasmScreen::DrawLine(const api::SPoint& inicio, const api::SPoint& fim, api::TColor cor, int largura)
{
    js_line(EscalaX(inicio.x), EscalaY(inicio.y), EscalaX(fim.x), EscalaY(fim.y), Cor(cor), Espessura(largura));
}

void CWasmScreen::DrawRect(const api::SRect& rect, api::TColor cor, int largura)
{
    DrawLine(Ponto(rect.left, rect.top), Ponto(rect.right, rect.top), cor, largura);
    DrawLine(Ponto(rect.right, rect.top), Ponto(rect.right, rect.bottom), cor, largura);
    DrawLine(Ponto(rect.right, rect.bottom), Ponto(rect.left, rect.bottom), cor, largura);
    DrawLine(Ponto(rect.left, rect.bottom), Ponto(rect.left, rect.top), cor, largura);
}

void CWasmScreen::DrawCircle(const api::SPoint& centro, int raio, api::TColor cor, int largura)
{
    js_circle(EscalaX(centro.x), EscalaY(centro.y), EscalaX(raio), Cor(cor), Espessura(largura));
}

void CWasmScreen::DrawRoundRect(const api::SRect& rect, int raio, api::TColor cor, int largura)
{
    const int x1 = EscalaX(rect.left);
    const int y1 = EscalaY(rect.top);
    const int x2 = EscalaX(rect.right);
    const int y2 = EscalaY(rect.bottom);
    js_round_rect(std::min(x1, x2), std::min(y1, y2), std::abs(x1 - x2) + 1, std::abs(y1 - y2) + 1, EscalaX(raio), Cor(cor),
                  Espessura(largura));
}

void CWasmScreen::DrawGrayGradient(const api::SRect& rect)
{
    const int x1 = EscalaX(rect.left);
    const int y1 = EscalaY(rect.top);
    const int x2 = EscalaX(rect.right);
    const int y2 = EscalaY(rect.bottom);
    js_gray_gradient(std::min(x1, x2), std::min(y1, y2), std::abs(x1 - x2) + 1, std::abs(y1 - y2) + 1);
}

void CWasmScreen::DrawTriangle(const api::SPoint& a, const api::SPoint& b, const api::SPoint& c, api::TColor cor,
                               int largura)
{
    DrawLine(a, b, cor, largura);
    DrawLine(b, c, cor, largura);
    DrawLine(c, a, cor, largura);
}

void CWasmScreen::DrawPolygon(const std::vector<api::SPoint>& pontos, api::TColor cor, int largura)
{
    if (pontos.size() < 2) {
        return;
    }
    for (size_t i = 1; i < pontos.size(); ++i) {
        DrawLine(pontos[i - 1], pontos[i], cor, largura);
    }
    DrawLine(pontos.back(), pontos.front(), cor, largura);
}

std::vector<api::SPathCommand> CWasmScreen::EscalaCaminho(const std::vector<api::SPathCommand>& caminho) const
{
    std::vector<api::SPathCommand> escalado;
    escalado.reserve(caminho.size());
    for (const api::SPathCommand& comando : caminho) {
        switch (comando.tipo) {
        case api::SPathCommand::MOVE_TO: {
            const double x = comando.x * m_escalaX;
            const double y = comando.y * m_escalaY;
            escalado.push_back({api::SPathCommand::MOVE_TO, x, y});
            break;
        }
        case api::SPathCommand::LINE_TO: {
            const double x = comando.x * m_escalaX;
            const double y = comando.y * m_escalaY;
            escalado.push_back({api::SPathCommand::LINE_TO, x, y});
            break;
        }
        case api::SPathCommand::ARC: {
            const double x = comando.x * m_escalaX;
            const double y = comando.y * m_escalaY;
            const double raioX = comando.raioX * m_escalaX;
            const double raioY = comando.raioY * m_escalaY;
            escalado.push_back({api::SPathCommand::ARC, x, y, raioX, raioY, comando.anguloInicial, comando.anguloVarredura});
            break;
        }
        case api::SPathCommand::CLOSE:
            escalado.push_back({api::SPathCommand::CLOSE});
            break;
        }
    }
    return escalado;
}

void CWasmScreen::FillPath(const std::vector<api::SPathCommand>& caminho, api::TColor cor)
{
    const std::vector<api::SPathCommand> escalado = EscalaCaminho(caminho);
    std::vector<int> tipos;
    std::vector<double> valores;
    tipos.reserve(escalado.size());
    valores.reserve(escalado.size() * 6);
    for (const api::SPathCommand& comando : escalado) {
        tipos.push_back(TipoCaminho(comando.tipo));
        valores.insert(valores.end(), {comando.x, comando.y, comando.raioX, comando.raioY, comando.anguloInicial,
                                       comando.anguloVarredura});
    }
    if (!tipos.empty()) {
        js_path(tipos.size(), tipos.data(), valores.data(), Cor(cor), 1, 1);
    }
}

void CWasmScreen::DrawPath(const std::vector<api::SPathCommand>& caminho, api::TColor cor, int largura)
{
    const std::vector<api::SPathCommand> escalado = EscalaCaminho(caminho);
    std::vector<int> tipos;
    std::vector<double> valores;
    tipos.reserve(escalado.size());
    valores.reserve(escalado.size() * 6);
    for (const api::SPathCommand& comando : escalado) {
        tipos.push_back(TipoCaminho(comando.tipo));
        valores.insert(valores.end(), {comando.x, comando.y, comando.raioX, comando.raioY, comando.anguloInicial,
                                       comando.anguloVarredura});
    }
    if (!tipos.empty()) {
        js_path(tipos.size(), tipos.data(), valores.data(), Cor(cor), 0, Espessura(largura));
    }
}

api::SRect CWasmScreen::DrawText(const api::SPoint& posicao, const api::IText& texto, const api::SFont& font,
                                 api::TColor cor, api::TColor fundo)
{
    api::TPosition largura = 0;
    api::TPosition altura = 0;
    GetFontMetrics(largura, altura, font, texto.GetText());
    api::TPosition esquerda = posicao.x;
    api::TPosition direita = esquerda + largura;
    switch (texto.GetAlignment()) {
    case api::ALINHAMENTO_CENTRO: {
        const api::TPosition metade = largura / 2;
        esquerda -= metade;
        direita -= metade;
        break;
    }
    case api::ALINHAMENTO_DIREITA:
        esquerda -= largura;
        direita -= largura;
        break;
    default:
        break;
    }
    const api::TPosition topo = posicao.y;
    api::SRect rect;
    rect.left = std::min(esquerda, direita);
    rect.right = std::max(esquerda, direita);
    const api::TPosition base = topo + altura;
    rect.top = std::min(topo, base);
    rect.bottom = std::max(topo, base);
    return DrawText(rect, texto, font, cor, fundo);
}

// not the target's yet (fn 9104): its substr(0, 40) of a temporary is C++23's rvalue substr, which the tree's
// -std=c++23 gives; the screen rectangle's selects differ, and the fragment has the measurement
api::SRect CWasmScreen::DrawText(const api::SRect& rect, const api::IText& texto, const api::SFont& font, api::TColor cor,
                                 api::TColor fundo)
{
    const std::string utf8 = ParaUtf8(texto.GetText());
    const int estilo = font.style;
    const int tamanho = EscalaY(font.size);
    api::TPosition largura = 0;
    api::TPosition altura = 0;
    GetFontMetrics(largura, altura, font, texto.GetText());
    largura = std::max<api::TPosition>(largura, 1);
    altura = std::max<api::TPosition>(altura, 1);

    api::SRect desenhado = Retangulo(rect.left, rect.top, largura, altura);
    switch (texto.GetAlignment()) {
    case api::ALINHAMENTO_CENTRO: {
        const api::TPosition largura1 = rect.right - rect.left + 1;
        const api::TPosition largura2 = desenhado.right - desenhado.left + 1;
        const api::TPosition x = rect.left + (largura1 - largura2) / 2;
        desenhado = Retangulo(x, rect.top, largura, altura);
        break;
    }
    case api::ALINHAMENTO_DIREITA:
        desenhado = Normaliza(rect.right - largura + 1, rect.top, rect.right, rect.top + altura - 1);
        break;
    default:
        break;
    }

    const int y1 = EscalaY(desenhado.top);
    const int y2 = EscalaY(desenhado.bottom);
    const int x1 = EscalaX(desenhado.left);
    const int x2 = EscalaX(desenhado.right);
    const int esquerda = std::min(x1, x2);
    const int direita = std::max(x1, x2);
    const int topo = std::min(y1, y2);
    const int base = std::max(y1, y2);
    if (fundo != 0) {
        js_fill(esquerda, topo, static_cast<api::TPosition>(direita - esquerda + 1),
                static_cast<api::TPosition>(base - topo + 1), Cor(fundo));
    }

    int xTexto;
    int alinhamento;
    if (texto.GetAlignment() == api::ALINHAMENTO_CENTRO) {
        xTexto = (esquerda + direita) / 2;
        alinhamento = 1;
    } else if (texto.GetAlignment() == api::ALINHAMENTO_DIREITA) {
        xTexto = direita;
        alinhamento = 2;
    } else {
        xTexto = esquerda;
        alinhamento = 0;
    }

    js_log((std::string("Write '") + texto.GetText().substr(0, 40) + "'").c_str());

    const api::TPosition recuo = static_cast<api::TPosition>(base - topo + 1) / -4;
    js_text(xTexto, static_cast<int>(std::ceil(m_escalaY + m_escalaY)) + recuo + base, direita - esquerda + 1, utf8.c_str(), tamanho,
            estilo & 1, (estilo >> 1) & 1, Cor(cor), alinhamento);
    return desenhado;
}

void CWasmScreen::DrawText(const api::SPoint& posicao, const api::SRect&, const api::IText& texto,
                           const api::SFont& font, api::TColor cor, api::TColor fundo)
{
    DrawText(posicao, texto, font, cor, fundo);
}

void CWasmScreen::DrawImage(const api::SPoint& posicao, const api::IImage& imagem, api::EAnchorPoint ancora)
{
    const std::vector<uint8_t> dados = imagem.GetData();
    const api::SPoint tamanho = m_ops.ImageSize(dados);
    const int largura = EscalaY(tamanho.x);
    const int altura = EscalaY(tamanho.y);
    int x = EscalaX(posicao.x);
    int y = EscalaY(posicao.y);
    Ancora(x, y, largura, altura, ancora);
    const api::SRect rect = Retangulo(x, y, std::max(largura, 1), std::max(altura, 1));
    if (!dados.empty()) {
        js_image(dados.data(), dados.size(), rect.left, rect.top, rect.right - rect.left + 1, rect.bottom - rect.top + 1);
    }
}

void CWasmScreen::DrawImagePlaceholder(const api::SPoint& posicao, const api::IImage&, api::EAnchorPoint ancora)
{
    const api::SRect rect = m_ops.ImageRect(64, 64, posicao, ancora);
    FillRect(rect, static_cast<api::TColor>(5));
    DrawRect(rect, static_cast<api::TColor>(3), 1);
}

void CWasmScreen::DrawImage(const api::SPoint& posicao, const api::IImage& imagem, const api::SPoint& tamanho,
                            api::EAnchorPoint ancora)
{
    const std::vector<uint8_t> dados = imagem.GetData();
    int largura = EscalaX(tamanho.x);
    int altura = EscalaY(tamanho.y);
    if (largura == 0 || altura == 0) {
        const api::SPoint natural = m_ops.ImageSize(dados);
        largura = EscalaY(natural.x);
        altura = EscalaY(natural.y);
    }
    int x = EscalaX(posicao.x);
    int y = EscalaY(posicao.y);
    Ancora(x, y, largura, altura, ancora);
    const api::SRect rect = Retangulo(x, y, std::max(largura, 1), std::max(altura, 1));
    if (!dados.empty()) {
        js_image(dados.data(), dados.size(), rect.left, rect.top, rect.right - rect.left + 1, rect.bottom - rect.top + 1);
    }
}

void CWasmScreen::DrawImage(const api::SPoint& posicao, const api::IImage& imagem, const api::SRect& rect)
{
    const std::vector<uint8_t> dados = imagem.GetData();
    if (!dados.empty()) {
        const int xa = posicao.x;
        const api::TPosition xb = xa + (rect.right - rect.left);
        const int ya = posicao.y;
        const api::TPosition yb = ya + (rect.bottom - rect.top);
        const int x1 = EscalaX(std::min<int>(xa, xb));
        const int x2 = EscalaX(std::max<int>(xa, xb));
        const int y1 = EscalaY(std::min<int>(ya, yb));
        const int y2 = EscalaY(std::max<int>(ya, yb));
        js_image(dados.data(), dados.size(), std::min(x1, x2), std::min(y1, y2), std::abs(x1 - x2) + 1,
                 std::abs(y1 - y2) + 1);
    }
}

void CWasmScreen::DrawMovie(const api::SPoint& posicao, const api::CMovie& filme, api::EAnchorPoint ancora)
{
    const int largura = EscalaY(filme.Tamanho().x);
    const int altura = EscalaY(filme.Tamanho().y);
    int x = EscalaX(posicao.x);
    int y = EscalaY(posicao.y);
    Ancora(x, y, largura, altura, ancora);
    const api::SRect rect = Retangulo(x, y, std::max(largura, 1), std::max(altura, 1));
    const std::vector<uebyte>& dados = filme.FrameAtual().imagem;
    if (!dados.empty()) {
        js_image(dados.data(), dados.size(), rect.left, rect.top, rect.right - rect.left + 1, rect.bottom - rect.top + 1);
    }
}

void CWasmScreen::Refresh()
{
    js_log("Refresh()");
    EmitEvent("vota:screen", "{\"refreshed\":true}");
}

void CWasmScreen::SetColors(api::TColor cor, api::TColor fundo)
{
    m_cor = cor;
    m_fundo = fundo;
}

int CWasmScreen::GetTextWidth(const std::string& texto, const api::SFont& font)
{
    const int tamanho = EscalaY(font.size);
    const int estilo = font.style;
    const std::string utf8 = ParaUtf8(texto);
    const int largura = js_measure_text_width(utf8.c_str(), tamanho, estilo & 1, (estilo >> 1) & 1);
    return static_cast<int>(std::ceil(largura / m_escalaX) + 1.0);
}

void CWasmScreen::Clear(int, api::TColor cor)
{
    Clear(cor);
}

} // namespace simulador
