#include "cwasmresource.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include "api/gui/cfixedimage.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp): a debug line of what a member did with a resource
extern "C" void js_resource_log(const char* acao, const char* recurso, const char* caminho, int tamanho);

namespace {

// a GIF's name with "Mulher4" before its extension (fn 4996)
std::string ComMulher(const std::string& caminho)
{
    const size_t ponto = caminho.rfind(".gif");
    if (ponto == std::string::npos) {
        return caminho;
    }
    std::string resultado = caminho;
    resultado.insert(ponto, "Mulher4");
    return resultado;
}

// the name without its leading ':', from the root
std::string Normaliza(const std::string& nome)
{
    if (nome.empty()) {
        return {};
    }
    std::string caminho = nome;
    while (!caminho.empty()) {
        if (caminho[0] != ':') {
            if (caminho[0] != '/') {
                caminho.insert(caminho.begin(), '/');
            }
            return caminho;
        }
        caminho.erase(0, 1);
    }
    return {};
}

// where a resource's file can be, in the order they are tried
std::vector<std::string> Candidatos(const std::string& nome)
{
    const std::string caminho = Normaliza(nome);
    if (caminho.empty()) {
        return {};
    }
    std::vector<std::string> candidatos = {caminho};
    if (caminho.rfind("/resource/images/", 0) == 0) {
        const std::string resto = caminho.substr(17);
        candidatos.push_back("/uenux/app/img/" + resto);
        candidatos.push_back("/pkg/img/" + resto);
    }
    if (caminho.rfind("/resource/gifs/", 0) == 0) {
        const std::string resto = caminho.substr(15);
        candidatos.push_back("/pkg/gifs/" + resto);
        candidatos.push_back(ComMulher(caminho));
        candidatos.push_back("/pkg/gifs/" + ComMulher(resto));
    }
    candidatos.erase(std::unique(candidatos.begin(), candidatos.end()), candidatos.end());
    return candidatos;
}

// whether a file opens
bool Existe(const std::string& caminho)
{
    std::ifstream arquivo(caminho, std::ios::binary);
    return arquivo.good();
}

// the first of the candidates that opens (fn 2626)
std::string Caminho(const std::string& nome)
{
    for (const std::string& candidato : Candidatos(nome)) {
        if (Existe(candidato)) {
            js_resource_log("resolve", nome.c_str(), candidato.c_str(), -1);
            return candidato;
        }
    }
    js_resource_log("missing", nome.c_str(), "", -1);
    return {};
}

// a file's bytes, none when it does not open (fn 3452)
std::vector<uebyte> Le(const std::string& caminho)
{
    std::ifstream arquivo(caminho, std::ios::binary);
    if (!arquivo) {
        return {};
    }
    return std::vector<uebyte>(std::istreambuf_iterator<char>(arquivo), std::istreambuf_iterator<char>());
}

// a big-endian 16-bit number of an image's header
uint16_t Le16(const uint8_t* bytes)
{
    return static_cast<uint16_t>(bytes[0] << 8 | bytes[1]);
}

// an image's width and height from its GIF, PNG or JPEG header, 1 by 1 when none gives them
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

api::SharedIImage CWasmResource::GetImage(const std::string& nome, int, int)
{
    const std::string caminho = Caminho(nome);
    std::vector<uebyte> dados = Le(caminho);
    js_resource_log("image", nome.c_str(), caminho.c_str(), dados.size());
    return std::make_shared<api::CFixedImage>(std::move(dados));
}

api::SharedVector CWasmResource::GetFile(const std::string& nome)
{
    const std::string caminho = Caminho(nome);
    std::vector<uebyte> dados = Le(caminho);
    js_resource_log("file", nome.c_str(), caminho.c_str(), dados.size());
    return std::make_shared<std::vector<uebyte>>(std::move(dados));
}

api::CMovie CWasmResource::GetMovie(const std::string& nome)
{
    const std::string caminho = Caminho(nome);
    std::vector<uebyte> dados = Le(caminho);
    js_resource_log("movie", nome.c_str(), caminho.c_str(), dados.size());
    const api::SPoint tamanho = TamanhoImagem(dados);
    return api::CMovie({api::CMovieFrame(std::move(dados), 80)}, tamanho);
}

bool CWasmResource::Exists(const std::string& nome)
{
    return !Caminho(nome).empty();
}

bool CWasmResource::IsResource(const std::string& nome)
{
    return !nome.empty() && nome[0] == ':';
}

} // namespace simulador
