// api::CStepsProgressBar (/home/rubio/tse/uenux2/src/api/gui/cstepsprogressbar.cpp). This comment is the
// reconstruction's. Target functions of this file:
//   13550 holds the constructor, CStepsProgressBar(const uedword, const std::vector<std::string> &, const SRect &,
//         seven const TColor), inlined there (vota::CPreShowProgressBar's slot 2); its throw is the record at line 428,
//         column 15, which stays free for it (not reconstructed)
//   3665 / 10973  ~CStepsProgressBar() (complete / deleting; out of line, the D0 calls the D2)
//   10969 GetTypeName() const, 10968 Rect() const, 10970 Move(const SPoint&)
//   5504  Draw(IScreen&) const, with the private Recalcula and the file-local Escolhe, CriaContorno and Fecha, which have
//         no target function of their own: Draw's callees in this file are 5505, 5506 and 5507 only
//   5507  Tenta, 5506 Divide, 10972 CabeEmUmaLinha and 10971 CabeProporcional, file-local; 10972 and 10971 are the table
//         slots 3442 and 3443 that Draw passes to Tenta (its i32.const at +0x2c8 and +0x385)
//   5505  std::vector<SSegmento>::__swap_out_circular_buffer, which the segments' reserve and push_back instantiate
// Of those Draw reaches, 5505 and 5507 match and the others differ: src/units/41-uenux2-cstepsprogressbar.mk has the
// scores. Every helper's name, and the lines of every function but the constructor's record, are a choice.

#include "api/gui/cstepsprogressbar.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/cfixedtext.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"

namespace api {

namespace {

const TFontSize TAMANHO_MINIMO = 10;
const int SETA = 10;
const int ESPACO = 4;

struct SDisposicao {
    TFontSize tamanhoFonte;
    std::vector<SRect> areas;
    std::vector<std::string> textos;
};

using Estrategia = bool (*)(IScreen& screen, const std::vector<std::string>& passos, const SRect& rect,
                            TFontSize tamanho, int seta, int espaco, std::vector<SRect>& areas);

std::vector<SRect> Divide(const SRect& rect, int partes, int seta, int espaco)
{
    if (partes == 0) {
        return {};
    }
    if (partes == 1) {
        return {rect};
    }
    const TPosition total = rect.right - rect.left + 1 + (partes - 1) * (seta - espaco);
    const TPosition largura = total / static_cast<TPosition>(partes);
    const TPosition topo = rect.top;
    const TPosition base = rect.bottom;
    std::vector<TPosition> larguras(partes, largura);
    const int resto = total % static_cast<TPosition>(partes);
    for (TPosition i = 0; i < resto; ++i) {
        ++larguras[i];
    }
    std::vector<SRect> areas;
    areas.reserve(partes);
    TPosition x = rect.left;
    for (int i = 0; i < partes; ++i) {
        const TPosition l = (i == partes - 1) ? rect.right - x + 1 : larguras[i];
        const TPosition fim = x + l - 1;
        areas.emplace_back(std::min(x, fim), std::min(topo, base), std::max(x, fim), std::max(topo, base));
        x += espaco - seta + l;
    }
    return areas;
}

bool CabeEmUmaLinha(IScreen& screen, const std::vector<std::string>& passos, const SRect& rect, TFontSize tamanho,
                    int seta, int espaco, std::vector<SRect>& areas)
{
    const size_t n = passos.size();
    if (passos.empty()) {
        areas.clear();
        return false;
    }
    TPosition largura;
    TPosition alturaTexto;
    areas = Divide(rect, n, seta, espaco);
    const SFont fonte{tamanho, 1};
    const TPosition altura = rect.bottom - rect.top + 1;
    for (size_t i = 0; i < n; ++i) {
        const std::string& texto = passos[i];
        alturaTexto = 0;
        largura = 0;
        screen.GetFontMetrics(largura, alturaTexto, fonte, texto);
        const TPosition margem = std::max<TPosition>(1, tamanho / 4);
        const TPosition alturaUtil = altura - 2 * margem;
        if (static_cast<TPosition>(alturaTexto - fonte.size / 5) > alturaUtil) {
            return false;
        }
        const SRect& area = areas[i];
        const TPosition recuo = tamanho * seta / std::max<TPosition>(1, altura);
        const TPosition disponivel = area.Width() - 2 * margem - (i > 0 ? seta : 0) - (i != n - 1 ? recuo : 0);
        if (static_cast<TPosition>(largura - fonte.size / 3) > disponivel) {
            return false;
        }
    }
    return true;
}

bool CabeProporcional(IScreen& screen, const std::vector<std::string>& passos, const SRect& rect, TFontSize tamanho,
                      int seta, int espaco, std::vector<SRect>& areas)
{
    const size_t n = passos.size();
    if (n == 0) {
        areas.clear();
        return false;
    }
    if (n == 1) {
        areas = {rect};
        return true;
    }
    const TPosition altura = rect.bottom - rect.top + 1;
    const TPosition larguraTotal = rect.right - rect.left + 1 + (n - 1) * (seta - espaco);
    const SFont fonte{tamanho, 1};
    std::vector<TPosition> minimos(n);
    std::vector<TPosition> pesos(n, 1);
    const TPosition margem = std::max<TPosition>(1, tamanho / 4);
    const TPosition alturaUtil = altura - 2 * margem;
    const TPosition recuo = tamanho * seta / std::max<TPosition>(1, altura);
    TPosition soma = 0;
    for (size_t i = 0; i < n; ++i) {
        TPosition largura = 0;
        TPosition alturaTexto = 0;
        screen.GetFontMetrics(largura, alturaTexto, fonte, passos[i]);
        if (static_cast<TPosition>(alturaTexto - fonte.size / 5) > alturaUtil) {
            return false;
        }
        const TPosition extra = (i > 0 ? seta : 0) + (i < n - 1 ? recuo : 0) + 2 * margem;
        const TPosition texto = largura - fonte.size / 3;
        minimos[i] = std::max<TPosition>(std::max<TPosition>(extra + 1, 2 * seta), extra + texto);
        pesos[i] = std::max<TPosition>(1, texto);
        soma += minimos[i];
    }
    if (soma > larguraTotal) {
        return false;
    }
    std::vector<TPosition> larguras(minimos);
    const TPosition sobra = larguraTotal - soma;
    TPosition somaPesos = 0;
    for (const TPosition peso : pesos) {
        somaPesos += peso;
    }
    int distribuido = 0;
    if (somaPesos > 0) {
        for (size_t i = 0; i < n - 1; ++i) {
            const TPosition acrescimo = pesos[i] * sobra / somaPesos;
            larguras[i] += acrescimo;
            distribuido += acrescimo;
        }
    }
    larguras.back() += sobra - distribuido;
    areas.clear();
    areas.reserve(n);
    TPosition x = rect.left;
    for (size_t i = 0; i < n; ++i) {
        const TPosition l = (i == n - 1) ? rect.right - x + 1 : larguras[i];
        areas.emplace_back(SRect::Normalized(x, rect.top, x + l - 1, rect.top + altura - 1));
        x += espaco - seta + l;
    }
    return true;
}

bool Tenta(IScreen& screen, const std::vector<std::string>& passos, const SRect& rect, TFontSize tamanho,
           Estrategia estrategia, SDisposicao& disposicao)
{
    for (int t = tamanho; t >= TAMANHO_MINIMO; --t) {
        std::vector<SRect> areas;
        if (estrategia(screen, passos, rect, t, SETA, ESPACO, areas)) {
            disposicao = SDisposicao{static_cast<TFontSize>(t), std::move(areas), passos};
            return true;
        }
    }
    return false;
}

SDisposicao Escolhe(IScreen& screen, const std::vector<std::string>& passos, const SRect& rect, TFontSize tamanho)
{
    SDisposicao umaLinha{TAMANHO_MINIMO, {}, passos};
    const bool cabeUmaLinha = Tenta(screen, passos, rect, tamanho, &CabeEmUmaLinha, umaLinha);
    SDisposicao proporcional{TAMANHO_MINIMO, {}, passos};
    const bool cabeProporcional = Tenta(screen, passos, rect, tamanho, &CabeProporcional, proporcional);
    if (cabeUmaLinha && !(cabeProporcional && umaLinha.tamanhoFonte < proporcional.tamanhoFonte)) {
        return umaLinha;
    }
    if (cabeProporcional) {
        return proporcional;
    }
    return SDisposicao{TAMANHO_MINIMO, Divide(rect, passos.size(), SETA, ESPACO), std::vector<std::string>(passos.size())};
}

SPathCommand Fecha()
{
    SPathCommand comando = SPathCommand();
    comando.tipo = SPathCommand::CLOSE;
    return comando;
}

std::vector<SPathCommand> CriaContorno(const SRect& area, bool primeiro, bool ultimo)
{
    const double altura = static_cast<TPosition>(area.bottom - area.top + 1);
    const double raio = std::min(10.0, altura * 0.5);
    const double diametro = raio * 2;
    const double largura = area.Width();
    const double topo = area.top;
    const double esquerda = area.left;
    std::vector<SPathCommand> contorno;
    if (primeiro && ultimo) {
        contorno.emplace_back(SPathCommand::MOVE_TO, esquerda + raio, topo);
        contorno.emplace_back(SPathCommand::ARC, esquerda, topo, diametro, diametro, 90, 90);
        const double base = topo + altura;
        contorno.emplace_back(SPathCommand::LINE_TO, esquerda, base - raio);
        contorno.emplace_back(SPathCommand::ARC, esquerda, base - diametro, diametro, diametro, 180, 90);
        const double direita = esquerda + largura;
        contorno.emplace_back(SPathCommand::LINE_TO, direita - raio, base);
        contorno.emplace_back(SPathCommand::ARC, direita - diametro, base - diametro, diametro, diametro, 270, 90);
        contorno.emplace_back(SPathCommand::LINE_TO, direita, topo + raio);
        contorno.emplace_back(SPathCommand::ARC, direita - diametro, topo, diametro, diametro, 0, 90);
        contorno.emplace_back(Fecha());
    } else if (primeiro) {
        contorno.emplace_back(SPathCommand::MOVE_TO, esquerda + raio, topo);
        contorno.emplace_back(SPathCommand::ARC, esquerda, topo, diametro, diametro, 90, 90);
        const double base = topo + altura;
        contorno.emplace_back(SPathCommand::LINE_TO, esquerda, base - raio);
        contorno.emplace_back(SPathCommand::ARC, esquerda, base - diametro, diametro, diametro, 180, 90);
        const double direita = esquerda + largura;
        contorno.emplace_back(SPathCommand::LINE_TO, direita - SETA, base);
        contorno.emplace_back(SPathCommand::LINE_TO, direita, topo + altura * 0.5);
        contorno.emplace_back(SPathCommand::LINE_TO, direita - SETA, topo);
        contorno.emplace_back(Fecha());
    } else if (ultimo) {
        contorno.emplace_back(SPathCommand::MOVE_TO, esquerda, topo);
        const double direita = esquerda + largura;
        contorno.emplace_back(SPathCommand::LINE_TO, direita - raio, topo);
        contorno.emplace_back(SPathCommand::ARC, direita - diametro, topo, diametro, diametro, 90, -90);
        const double base = topo + altura;
        contorno.emplace_back(SPathCommand::LINE_TO, direita, base - raio);
        contorno.emplace_back(SPathCommand::ARC, direita - diametro, base - diametro, diametro, diametro, 0, -90);
        contorno.emplace_back(SPathCommand::LINE_TO, esquerda, base);
        contorno.emplace_back(SPathCommand::LINE_TO, esquerda + SETA, topo + altura * 0.5);
        contorno.emplace_back(Fecha());
    } else {
        contorno.emplace_back(SPathCommand::MOVE_TO, esquerda, topo);
        const double direita = esquerda + largura;
        contorno.emplace_back(SPathCommand::LINE_TO, direita - SETA, topo);
        contorno.emplace_back(SPathCommand::LINE_TO, direita, topo + altura * 0.5);
        const double base = topo + altura;
        contorno.emplace_back(SPathCommand::LINE_TO, direita - SETA, base);
        contorno.emplace_back(SPathCommand::LINE_TO, esquerda, base);
        contorno.emplace_back(SPathCommand::LINE_TO, esquerda + SETA, topo + altura * 0.5);
        contorno.emplace_back(Fecha());
    }
    return contorno;
}

} // namespace

// (original lines 263-424: content not recovered)
#line 425
// <stubs>
// f13550 · 2118 B · unmatched · name unknown
// void f13550(i32, i32) { ... }
// </stubs>






CStepsProgressBar::~CStepsProgressBar() = default;

void CStepsProgressBar::Recalcula(IScreen& screen) const
{
    if (!m_recalcular) {
        return;
    }
    const size_t n = m_passos.size();
    m_segmentos.clear();
    m_segmentos.reserve(n);
    const TPosition altura = m_rect.bottom - m_rect.top + 1;
    const TFontSize tamanho = std::min<TFontSize>(std::max<TFontSize>(altura * 3 / 5, TAMANHO_MINIMO), altura);
    const SDisposicao disposicao = Escolhe(screen, m_passos, m_rect, tamanho);
    const SFont fonte{disposicao.tamanhoFonte, 1};
    m_font = fonte;
    for (size_t i = 0; i < n; ++i) {
        const std::string& texto = disposicao.textos[i];
        TPosition largura = 0;
        TPosition alturaTexto = 0;
        if (!texto.empty()) {
            screen.GetFontMetrics(largura, alturaTexto, m_font, texto);
        }
        const SRect& area = disposicao.areas[i];
        const TPosition topoArea = area.top;
        const TPosition margem = std::max<TPosition>(1, m_font.size / 4);
        const TPosition topo = topoArea + margem;
        const TPosition alturaUtil = std::max<TPosition>(topo, area.bottom - margem) - topo + 1;
        const TPosition folga = (alturaUtil - alturaTexto) / 2;
        const SPoint posicao{static_cast<TPosition>(area.left + margem + (i > 0 ? SETA : 0)),
                             static_cast<TPosition>(topo + std::max<TPosition>(0, folga))};
        m_segmentos.push_back({CriaContorno(area, i == 0, i == n - 1), posicao, texto});
    }
    m_recalcular = false;
}

void CStepsProgressBar::Draw(IScreen& screen) const
{
    if (m_passos.empty()) {
        return;
    }
    Recalcula(screen);
    for (size_t i = 0; i < m_segmentos.size(); ++i) {
        const SSegmento& segmento = m_segmentos[i];
        screen.DrawPath(segmento.contorno, m_corBorda, 1);
        if (i < m_passoAtual) {
            screen.FillPath(segmento.contorno, m_corFundoFeito);
            if (!segmento.texto.empty()) {
                screen.DrawText(segmento.posicaoTexto, CFixedText(segmento.texto), m_font, m_corTextoFeito,
                                static_cast<TColor>(0));
            }
        } else {
            const bool atual = i == m_passoAtual;
            screen.FillPath(segmento.contorno, atual ? m_corFundoAtual : m_corFundoPendente);
            if (!segmento.texto.empty()) {
                screen.DrawText(segmento.posicaoTexto, CFixedText(segmento.texto), m_font,
                                atual ? m_corTextoAtual : m_corTextoPendente, static_cast<TColor>(0));
            }
        }
    }
}

void CStepsProgressBar::Move(const SPoint& posicao)
{
    if (posicao.x == m_rect.left && posicao.y == m_rect.top) {
        return;
    }

    m_rect.Move(posicao);
    m_recalcular = true;
    m_segmentos.clear();

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

std::string CStepsProgressBar::GetTypeName() const
{
    return "CStepsProgressBar";
}

SRect CStepsProgressBar::Rect() const
{
    return m_rect;
}

} // namespace api
