// comum::md::CTradutorFrase: RecuperaLabel, TraduzLabel and TraduzTexto at their records' lines, then TraduzData and
// Traduz. The reconstruction's own note; the blank lines stand for text not recovered.
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"

#include <utility>
#include <vector>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

using ecourna::api::util::CStringUtils;

std::map<char, ecourna::app::dados::CLabelParametrizado> CTradutorFrase::s_labels;
api::CDate CTradutorFrase::s_dataReferencia;


namespace {

std::pair<std::string, std::string> Separa(std::string& texto, size_t inicio, size_t fim)
{
    const std::string prefixo = texto.substr(0, inicio);
    texto.erase(0, inicio);
    const std::string marcador = texto.substr(0, fim - inicio);
    texto.erase(0, fim - inicio);
    return {prefixo, marcador};
}

} // namespace

std::string CTradutorFrase::Traduz(const std::string& frase)
{
    if (s_labels.empty()) {
        return frase;
    }

    std::string chaves = "[";
    for (const auto& [chave, label] : s_labels) {
        chaves.append(1, chave);
    }
    chaves += "]";

    const std::string expressaoLabel = "<" + chaves + "[CL][PS][ABN]>";
    const std::string campo = "[^|>]*";
    const std::string expressaoTexto = "<" + chaves + "\\|" + campo + "\\|" + campo + "\\|" + campo + ">";
    const std::string expressaoData = "<DT[+-][0-9]+>";

    std::string texto = frase;
    std::string traducao;
    while (!texto.empty()) {
        const std::pair<size_t, size_t> label = CStringUtils::FindRegex(expressaoLabel, texto);
        const std::pair<size_t, size_t> textoParametrizado = CStringUtils::FindRegex(expressaoTexto, texto);
        const std::pair<size_t, size_t> data = CStringUtils::FindRegex(expressaoData, texto);
        const std::pair<size_t, size_t>& anterior = label.first < textoParametrizado.first ? label : textoParametrizado;
        const std::pair<size_t, size_t>& proximo = anterior.first < data.first ? anterior : data;
        const size_t inicio = proximo.first;
        const size_t fim = proximo.second;

        const auto [prefixo, marcador] = Separa(texto, inicio, fim);
        traducao += prefixo;
        if (!marcador.empty()) {
            const std::string conteudo = marcador.substr(1, marcador.size() - 2);
            if (inicio == label.first && fim == label.second) {
                traducao += TraduzLabel(conteudo);
            } else if (inicio == textoParametrizado.first && fim == textoParametrizado.second) {
                traducao += TraduzTexto(conteudo);
            } else {
                traducao += TraduzData(conteudo);
            }
        }
    }
    return traducao;
}

// (original lines 76-89: content not recovered)
#line 90
const ecourna::app::dados::CLabelParametrizado& CTradutorFrase::RecuperaLabel(const std::string& label)
{
    const char token = label.at(0);
    const auto it = s_labels.find(token);
    if (it == s_labels.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8128, "Token inválido: " + label);
    }
    return it->second;
}


std::string CTradutorFrase::TraduzLabel(const std::string& label)
{
    if (label.size() != 4) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8129, "Label inválido: " + label);
    }

    const ecourna::app::dados::CLabelParametrizado& parametrizado = RecuperaLabel(label);
    const std::string tipo = label.substr(1, 2);
    std::string traducao;
    if (tipo == "CS") {
        traducao = parametrizado.GetCurto();
    } else if (tipo == "CP") {
        traducao = parametrizado.GetCurtoPlural();
    } else if (tipo == "LS") {
        traducao = parametrizado.GetLongo();
    } else if (tipo == "LP") {
        traducao = parametrizado.GetLongoPlural();
    } else {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8130, "Label inválido: " + label);
    }

    switch (label.at(3)) {
        case 'A':
            CStringUtils::ToUpper(traducao);
            break;
        case 'B':
            CStringUtils::ToLower(traducao);
            break;
        case 'N':
            break;
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_8131, "Label inválido: " + label);
    }
    return traducao;
}

std::string CTradutorFrase::TraduzTexto(const std::string& texto)
{
    const std::vector<std::string> partes = CStringUtils::Split(texto, '|');
    if (partes.size() != 4) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8132, "Texto inválido: " + texto);
    }

    const auto genero = RecuperaLabel(texto).GetGenero();
    switch (genero) {
        case ecourna::app::dados::CLabelParametrizado::EGL_NEUTRO:
            return partes.at(1);
        case ecourna::app::dados::CLabelParametrizado::EGL_MASCULINO:
            return partes.at(2);
        case ecourna::app::dados::CLabelParametrizado::EGL_FEMININO:
            return partes.at(3);
        default:
            break;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8133, "Texto inválido: " + texto);
}

std::string CTradutorFrase::TraduzData(const std::string& data)
{
    const std::string numero = data.substr(3);
    const ueword dias = CStringUtils::ToWord(numero);
    const std::string sinal = data.substr(2, 1);
    const api::CDate referencia = sinal == "+" ? s_dataReferencia + dias : s_dataReferencia - dias;
    return referencia.Format("DD/MM/YYYY");
}

} // namespace comum::md
