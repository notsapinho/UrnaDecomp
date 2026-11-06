// Reconstruction's note: of this file the reconstruction holds the INI reader's string helpers (target fns 5485, 2236,
// 2235, 2234, 3651 and TerminaComBarraInvertida, 5484) and CIniStrings::ParseKeyLine, whose records are lines 183 and
// 187; every other line is a choice (src/units/379-uenux2-cinifile.mk and 215-uenux2-api-app-leftovers.mk).
#include "api/io/cinistrings.h"

#include <algorithm>
#include <cctype>
#include <format>
#include <utility>

#include "api/io/eueioerror.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

namespace {

const std::vector<std::pair<std::string, char>> ESCAPES = {
    {"\\n", '\n'}, {"\\t", '\t'}, {"\\;", ';'}, {"\\:", ':'}, {"\\=", '='},
    {"\\#", '#'}, {"\\ ", ' '}, {"\\[", '['}, {"\\]", ']'}, {"\\\\", '\\'},
};

bool EhEspaco(char c)
{
    return std::isspace(c) || std::isblank(c);
}

} // namespace

bool LinhaUtil(const std::string& linha)
{
    return !RemoveEspacos(RemoveComentario(linha)).empty();
}

std::string RemoveComentario(const std::string& linha)
{
    std::string::size_type fim = std::string::npos;
    for (char c : "#;") {
        fim = std::min(fim, ProcuraNaoEscapado(linha, std::string(1, c)));
    }
    if (fim != std::string::npos) {
        return linha.substr(0, fim);
    }
    return linha;
}

std::string RemoveEspacos(const std::string& texto)
{
    std::string::size_type inicio = 0;
    while (inicio < texto.size() && EhEspaco(texto[inicio])) {
        ++inicio;
    }
    std::string::size_type fim = texto.size() - 1;
    while (fim > inicio && EhEspaco(texto[fim])) {
        std::string::size_type barras = 0;
        while (fim >= barras + 1 && texto[fim - barras - 1] == '\\') {
            ++barras;
        }
        if (barras % 2 != 0) {
            break;
        }
        --fim;
    }
    return texto.substr(inicio, fim - inicio + 1);
}

std::string::size_type ProcuraNaoEscapado(const std::string& texto, const std::string& procurado)
{
    const std::string::size_type pos = texto.find(procurado);
    if (pos == 0) {
        return 0;
    }
    if (pos == std::string::npos) {
        return std::string::npos;
    }
    const std::string::size_type anterior = texto.find_last_not_of('\\', pos - 1);
    const std::string::size_type barras = anterior == std::string::npos ? pos : pos - anterior - 1;
    if (barras % 2 == 0) {
        return pos;
    }
    const std::string::size_type resto = ProcuraNaoEscapado(texto.substr(pos + 1), procurado);
    return resto == std::string::npos ? std::string::npos : resto + pos + 1;
}

bool EhSecao(const std::string& linha)
{
    return linha.size() >= 2 && linha.front() == '[' && linha.back() == ']';
}

std::string TrataEscapes(const std::string& texto)
{
    std::string resultado = RemoveEspacos(RemoveComentario(texto));
    for (const auto& escape : ESCAPES) {
        resultado = ecourna::api::util::CStringUtils::Replace(std::as_const(resultado), escape.first,
            std::string(1, escape.second));
    }
    return resultado;
}

// (original lines 101-177: content not recovered)
#line 178
void CIniStrings::ParseKeyLine(std::string& nome, std::string& valor, const std::string& linha)
{
    const std::string texto = RemoveEspacos(RemoveComentario(linha));
    const std::string::size_type igual = ProcuraNaoEscapado(texto, "=");
    if (igual == std::string::npos) {
        throw CUeIoError(EUE_IO_LINHA_INVALIDA, std::format("Linha inválida [{}]", texto));
    }
    nome = TrataEscapes(texto.substr(0, igual));
    if (nome.empty()) {
        throw CUeIoError(EUE_IO_NOME_CHAVE_INVALIDO, std::format("Linha com nome inválido [{}]", texto));
    }
    valor = TrataEscapes(texto.substr(igual + 1));
}

bool TerminaComBarraInvertida(const std::string& linha)
{
    if (linha.empty()) {
        return false;
    }
    std::string::size_type i = linha.size() - 1;
    if (linha[i] != '\\') {
        return false;
    }
    bool impar = true;
    while (i > 0 && linha[--i] == '\\') {
        impar = !impar;
    }
    return impar;
}

} // namespace api
