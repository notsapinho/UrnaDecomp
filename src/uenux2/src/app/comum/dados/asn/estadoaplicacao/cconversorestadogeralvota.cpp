// Reconstruction: comum::asn::CConversorEstadoGeralVota (target fns 11390 and 11391, its slots 2 and 3, with the four
// helpers binaryen inlines into them). Each throw sits on its record's line; the other lines are blank where the
// original is not recovered, and where DoDesconverte and DoConverte start is chosen. Fragment 172 has the choices.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeralvota.h"

#include <format>

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversornumviasimpressasrelatorios.h"
#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {


CConversorEstadoGeralVota::TDado CConversorEstadoGeralVota::DoDesconverte(const TEntidade& entidade) const
{
    const EEstadoVota estadoVota = DesconverteEstadoVota(entidade.get_estadoVota());
    const EEstadoEncerramento estadoEncerramento = DesconverteEstadoEncerramento(entidade.get_estadoEncerramento());
    const uebyte qtdBU = entidade.get_qtdBU().getValue();
    std::optional<uedword> urnaIdGerouZeresima;
    if (entidade.urnaIdGerouZeresima_isPresent()) {
        urnaIdGerouZeresima = entidade.get_urnaIdGerouZeresima().getValue();
    }
    std::optional<api::CDateTime> dhIniAquisicao;
    if (entidade.dhIniAquisicao_isPresent()) {
        dhIniAquisicao = Utils::DesconverteDataHoraJE(entidade.get_dhIniAquisicao());
    }
    std::optional<api::CDateTime> dhFimAquisicao;
    if (entidade.dhFimAquisicao_isPresent()) {
        dhFimAquisicao = Utils::DesconverteDataHoraJE(entidade.get_dhFimAquisicao());
    }
    const ueword comparecimento = entidade.get_comparecimento().getValue();
    const ueword qtdJustificativa = entidade.get_qtdJustificativa().getValue();
    std::optional<api::CDateTime> dhUltimoVoto;
    if (entidade.dhUltimoVoto_isPresent()) {
        dhUltimoVoto = Utils::DesconverteDataHoraJE(entidade.get_dhUltimoVoto());
    }
    const bool treinamentoEleitor = entidade.get_treinamentoEleitor();
    const CConversorNumViasImpressasRelatorios conversorNumVias;
    const md::estadoaplicacao::CNumViasImpressasRelatorios numViasImpressasRelatorios =
        conversorNumVias.Desconverte(entidade.get_numViasImpressasRelatorios());
    std::optional<api::CDateTime> dhEmissao;
    if (entidade.dhEmissao_isPresent()) {
        dhEmissao = Utils::DesconverteDataHoraJE(entidade.get_dhEmissao());
    }
    const bool tecladoTestadoPosConversao = entidade.get_tecladoTestadoPosConversao();
    return TDado(estadoVota, estadoEncerramento, qtdBU, urnaIdGerouZeresima, dhIniAquisicao, dhFimAquisicao,
                 comparecimento, qtdJustificativa, dhUltimoVoto, treinamentoEleitor, numViasImpressasRelatorios,
                 dhEmissao, tecladoTestadoPosConversao);
}

CConversorEstadoGeralVota::TEntidade CConversorEstadoGeralVota::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_estadoVota(ConverteEstadoVota(dado.GetEstadoVota()));
    entidade.set_estadoEncerramento(ConverteEstadoEncerramento(dado.GetEstadoEncerramento()));
    entidade.set_qtdBU(dado.GetQtdBU());
    if (dado.GetUrnaIdGerouZeresima()) {
        entidade.set_urnaIdGerouZeresima(*dado.GetUrnaIdGerouZeresima());
    } else {
        entidade.omit_urnaIdGerouZeresima();
    }
    if (dado.GetDhIniAquisicao()) {
        entidade.set_dhIniAquisicao() = Utils::ConverteDataHoraJE(*dado.GetDhIniAquisicao());
    } else {
        entidade.omit_dhIniAquisicao();
    }
    if (dado.GetDhFimAquisicao()) {
        entidade.set_dhFimAquisicao() = Utils::ConverteDataHoraJE(*dado.GetDhFimAquisicao());
    } else {
        entidade.omit_dhFimAquisicao();
    }
    entidade.set_comparecimento(dado.GetComparecimento());
    entidade.set_qtdJustificativa(dado.GetQtdJustificativa());
    if (dado.GetDhUltimoVoto()) {
        entidade.set_dhUltimoVoto() = Utils::ConverteDataHoraJE(*dado.GetDhUltimoVoto());
    } else {
        entidade.omit_dhUltimoVoto();
    }
    entidade.set_treinamentoEleitor(dado.GetTreinamentoEleitor());
    const CConversorNumViasImpressasRelatorios conversorNumVias;
    entidade.set_numViasImpressasRelatorios() = conversorNumVias.Converte(dado.GetNumViasImpressasRelatorios());
    if (dado.GetDhEmissao()) {
        entidade.set_dhEmissao() = Utils::ConverteDataHoraJE(*dado.GetDhEmissao());
    } else {
        entidade.omit_dhEmissao();
    }
    entidade.set_tecladoTestadoPosConversao(dado.GetTecladoTestadoPosConversao());
    return entidade;
}

// (original lines 93-115: content not recovered)
#line 116
ModuloEstadoGeralVota::EstadoVota CConversorEstadoGeralVota::ConverteEstadoVota(const EEstadoVota estado) const
{
    switch (estado) {
        case EAVINICIAL:
            return ModuloEstadoGeralVota::EstadoVota::inicial;
        case EAVGERADADOSDINAMICOS:
            return ModuloEstadoGeralVota::EstadoVota::gerabasedinamica;
        case EAVAGUARDAHORAZERESIMA:
            return ModuloEstadoGeralVota::EstadoVota::aguardahorazeresima;
        case EAVGERARZE:
            return ModuloEstadoGeralVota::EstadoVota::gerarze;
        case EAVZERESIMAGERADA:
            return ModuloEstadoGeralVota::EstadoVota::zeresimagerada;
        case EAVZERESIMAIMPRESSA:
            return ModuloEstadoGeralVota::EstadoVota::zeresimaimpressa;
        case EAVREGISTROMESARIOINICIAL:
            return ModuloEstadoGeralVota::EstadoVota::registromesarioinicial;
        case EAVVOTAR:
            return ModuloEstadoGeralVota::EstadoVota::votar;
        case EAVFIMAQUISICAOVOTOS:
            return ModuloEstadoGeralVota::EstadoVota::fimaquisicaovotos;
        case EAVREGISTROMESARIOFINAL:
            return ModuloEstadoGeralVota::EstadoVota::registromesariofinal;
        case EAVGERARBU:
            return ModuloEstadoGeralVota::EstadoVota::gerarbu;
        case EAVGERARRELATORIOS:
            return ModuloEstadoGeralVota::EstadoVota::gerarrelatorios;
        case EAVIMPRIMIRBU:
            return ModuloEstadoGeralVota::EstadoVota::imprimirbu;
        case EAVGRAVARRESULTADOS:
            return ModuloEstadoGeralVota::EstadoVota::gravarresultados;
        case EAVCOPIARESULTADOSMR:
            return ModuloEstadoGeralVota::EstadoVota::copiaresultadosmr;
        case EAVENCERRADA:
            return ModuloEstadoGeralVota::EstadoVota::encerrada;
        case EAVULTIMOID:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7929,
                                     std::format("Valor inválido para EEstadoVota: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7930,
                             std::format("Valor inválido para EEstadoVota: {}", estado));
}

// (original lines 160-161: content not recovered)
#line 162
EEstadoVota CConversorEstadoGeralVota::DesconverteEstadoVota(const ModuloEstadoGeralVota::EstadoVota& estado) const
{
    switch (estado) {
        case ModuloEstadoGeralVota::EstadoVota::inicial:
            return EAVINICIAL;
        case ModuloEstadoGeralVota::EstadoVota::gerabasedinamica:
            return EAVGERADADOSDINAMICOS;
        case ModuloEstadoGeralVota::EstadoVota::aguardahorazeresima:
            return EAVAGUARDAHORAZERESIMA;
        case ModuloEstadoGeralVota::EstadoVota::gerarze:
            return EAVGERARZE;
        case ModuloEstadoGeralVota::EstadoVota::zeresimagerada:
            return EAVZERESIMAGERADA;
        case ModuloEstadoGeralVota::EstadoVota::zeresimaimpressa:
            return EAVZERESIMAIMPRESSA;
        case ModuloEstadoGeralVota::EstadoVota::registromesarioinicial:
            return EAVREGISTROMESARIOINICIAL;
        case ModuloEstadoGeralVota::EstadoVota::votar:
            return EAVVOTAR;
        case ModuloEstadoGeralVota::EstadoVota::fimaquisicaovotos:
            return EAVFIMAQUISICAOVOTOS;
        case ModuloEstadoGeralVota::EstadoVota::registromesariofinal:
            return EAVREGISTROMESARIOFINAL;
        case ModuloEstadoGeralVota::EstadoVota::gerarbu:
            return EAVGERARBU;
        case ModuloEstadoGeralVota::EstadoVota::gerarrelatorios:
            return EAVGERARRELATORIOS;
        case ModuloEstadoGeralVota::EstadoVota::imprimirbu:
            return EAVIMPRIMIRBU;
        case ModuloEstadoGeralVota::EstadoVota::gravarresultados:
            return EAVGRAVARRESULTADOS;
        case ModuloEstadoGeralVota::EstadoVota::copiaresultadosmr:
            return EAVCOPIARESULTADOSMR;
        case ModuloEstadoGeralVota::EstadoVota::encerrada:
            return EAVENCERRADA;
        case ModuloEstadoGeralVota::EstadoVota::exibealertadesligamento:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7931,
                                     std::format("Estado não deve ser usado: {}", estado));

        case ModuloEstadoGeralVota::EstadoVota::unknownEnumeration_:
        case ModuloEstadoGeralVota::EstadoVota::ultimoid:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7932,
                                     std::format("Valor inválido para EstadoVota: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7933,
                             std::format("Valor inválido para EstadoVota: {}", estado));
}


ModuloEstadoGeralVota::EstadoEncerramento CConversorEstadoGeralVota::ConverteEstadoEncerramento(
    const EEstadoEncerramento estado) const
{
    switch (estado) {
        case EAEINICIAL:
            return ModuloEstadoGeralVota::EstadoEncerramento::inicial;
        case EAEIMPRIMIROBRIGATORIABU:
            return ModuloEstadoGeralVota::EstadoEncerramento::imprimirobrigatoriabu;
        case EAERETIRAMR:
            return ModuloEstadoGeralVota::EstadoEncerramento::retirarmr;
        case EAEFIMDOSTRABALHOS:
            return ModuloEstadoGeralVota::EstadoEncerramento::fimdostrabalhos;
        case EAEULTIMOID:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7934,
                                     std::format("Valor não suportado para EEstadoEncerramento: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7935,
                             std::format("Valor inválido para EEstadoEncerramento: {}", estado));
}


EEstadoEncerramento CConversorEstadoGeralVota::DesconverteEstadoEncerramento(
    const ModuloEstadoGeralVota::EstadoEncerramento& estado) const
{
    switch (estado) {
        case ModuloEstadoGeralVota::EstadoEncerramento::inicial:
            return EAEINICIAL;
        case ModuloEstadoGeralVota::EstadoEncerramento::imprimirobrigatoriabu:
            return EAEIMPRIMIROBRIGATORIABU;
        case ModuloEstadoGeralVota::EstadoEncerramento::retirarmr:
            return EAERETIRAMR;
        case ModuloEstadoGeralVota::EstadoEncerramento::fimdostrabalhos:
            return EAEFIMDOSTRABALHOS;
        case ModuloEstadoGeralVota::EstadoEncerramento::unknownEnumeration_:
        case ModuloEstadoGeralVota::EstadoEncerramento::ultimoid:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7936,
                                     std::format("Valor não suportado para EstadoEncerramento: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7937,
                             std::format("Valor inválido para EstadoEncerramento: {}", estado));
}

} // namespace comum::asn

// <stubs>
// f5329 · 20 B · unmatched · placement: link order · name unknown
// void f5329(i32, i32) { ... }
// </stubs>
