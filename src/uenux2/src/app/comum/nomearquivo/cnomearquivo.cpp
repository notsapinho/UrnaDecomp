// The anonymous-namespace helpers of /home/rubio/tse/uenux2/src/app/comum/nomearquivo/cnomearquivo.cpp, and two of
// the file's name builders. The helpers' throws are records of the target, so their positions in this file are fixed:
//   2828  FormataFase(EUrnaFase)                   record at line 38, column 19
//   1161  FormataNumero(uedword, uedword)          record at line 48, column 15
//   3773  FormataUF(const std::string &)           record at line 73, column 15
// The record at line 208, ajustaAbrangenciaUFMunicipio's, which fn 3744 holds, is not written. The builders (fns 1705
// and 3772) have no record: their names and lines are chosen (src/units/131-uenux2-cnomearquivo.mk).

#include "app/comum/nomearquivo/cnomearquivo.h"

#include <format>

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/nomearquivo/euecomumnomearquivoerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

namespace {

// (original lines 21-27: content not recovered)
#line 28
std::string FormataFase(EUrnaFase fase)
{
    switch (fase) {
        case FASE_OFICIAL:
            return "o";
        case FASE_SIMULADO:
            return "s";
        case FASE_TREINAMENTO:
            return "t";
        default:
            throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_FASE_INVALIDA, std::format("Fase inválida: {}", fase));
    }
}

// (original lines 42-43: content not recovered)
#line 44
std::string FormataNumero(uedword numero, uedword casas)
{
    std::string texto = std::format("{:0{}}", numero, casas);
    if (texto.size() > casas) {
        throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_NUMERO_EXCEDE_CASAS,
            std::format("Número ultrapassou o tamanho máximo de {} casas em [{}]", casas, texto));
    }
    return texto;
}

// (original lines 54-69: content not recovered)
#line 70
std::string FormataUF(const std::string& uf)
{
    if (uf.size() != 2) {
        throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_UF_INVALIDA, std::format("UF inválida: [{}]", uf));
    }
    return ecourna::api::util::CStringUtils::ToLower(uf);
}

} // namespace

std::string CNomeArquivo::NomeArquivoUF(EUrnaFase fase, uedword pleito, const std::string& uf, const std::string& tipo,
    const std::string& extensao)
{
    return FormataFase(fase) + FormataNumero(pleito, 5) + FormataUF(uf) + ("-" + tipo) + "." + extensao;
}

std::string CNomeArquivo::NomeArquivoSecao(EUrnaFase fase, uedword pleito, const std::string& uf, uedword municipio,
    uedword zona, uedword secao, const std::string& tipo, const std::string& extensao)
{
    return FormataFase(fase) + FormataNumero(pleito, 5) + FormataUF(uf) + FormataNumero(municipio, 5) +
           FormataNumero(zona, 4) + FormataNumero(secao, 4) + ("-" + tipo) + "." + extensao;
}

} // namespace comum

// <stubs>
// f3744 · 2521 B · unmatched · name unknown
// void f3744(i32, i32, i32, i32, i32, i32, i32) { ... }
// </stubs>
