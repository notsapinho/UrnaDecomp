// comum::CGravadorUtil (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorutil.cpp). Its throws are records of
// the target, so their positions in this file are fixed:
//   DeterminaNomeArquivoSemLetra    records at lines 28, 33 and 38, column 15 (inlined by binaryen into fn 3798)
//   3798  DeterminaNomeArquivo        no record: its line is a choice, after the function it calls
//   2274  ConverteFase                record at line 97, column 19
//   ConverteFaseEcourna             record at line 113, column 19 (no index: inlined by binaryen into fn 12098)
//   ConverteSituacaoArquivoEcourna  record at line 129, column 11 (no index; no function loads the record: 12098 holds
//                                   its frame and the result 0 alone, its argument a constant every caller passed)
// The two functions' first lines are a choice; src/units/122-uenux2-app-comum-gravadores.mk says what their bodies rest
// on and what is chosen (the characters 'f' and 'p', the code 8699).

#include "app/comum/gravadores/cgravadorutil.h"

#include <format>

#include "app/comum/carquivosresultado.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum {


std::string CGravadorUtil::DeterminaNomeArquivoSemLetra(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase)
{

    if (municipio >= 100000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8645, std::format("Município inválido: {}", municipio));
    }


    if (zona >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8646, std::format("Zona inválida: {}", zona));
    }


    if (secao >= 10000) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8647, std::format("Seção inválida: {}", secao));
    }

    return std::format("{:c}{:05}{}{:05}{:04}{:04}-", fase, CConfiguracaoEleicao::GetInst().GetPleito().GetID(),
        CLocal::GetInst().GetUFMinuscula(), municipio, zona, secao);
}

std::string CGravadorUtil::DeterminaNomeArquivo(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao)
{
    return DeterminaNomeArquivoSemLetra(municipio, zona, secao, fase) + CArquivosResultado::GetInst()[extensao];
}

// (original lines 51-86: content not recovered)
#line 87
EUrnaFase CGravadorUtil::ConverteFase(const char fase)
{
    switch (fase) {
        case 't':
            return FASE_TREINAMENTO;
        case 's':
            return FASE_SIMULADO;
        case 'o':
            return FASE_OFICIAL;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8649, std::format("Fase inválida: {:#x}", fase));
    }
}

// (original lines 101-102: content not recovered)
#line 103
ecourna::app::dados::TFaseID CGravadorUtil::ConverteFaseEcourna(char fase)
{
    switch (fase) {
        case 't':
            return ecourna::app::dados::CFaseID::FASE_TREINAMENTO;
        case 's':
            return ecourna::app::dados::CFaseID::FASE_SIMULADO;
        case 'o':
            return ecourna::app::dados::CFaseID::FASE_OFICIAL;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8698, std::format("Fase inválida: {:#x}", fase));
    }
}

// (original lines 117-118: content not recovered)
#line 119
ecourna::app::dados::CResultadoUrnaCadastro::ESituacaoArquivo
CGravadorUtil::ConverteSituacaoArquivoEcourna(char situacao)
{
    switch (situacao) {
        case 'f':
            return ecourna::app::dados::CResultadoUrnaCadastro::ArquivoFinal;
        case 'p':
            return ecourna::app::dados::CResultadoUrnaCadastro::ArquivoParcial;
    }

    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8699, std::format("Situação arquivo inválida: {}", situacao));
}

} // namespace comum
