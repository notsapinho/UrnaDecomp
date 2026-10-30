// Reconstruction: comum::asn::CConversorEstadoGeralSA (target fns 11392, 11393). ConverteEstadoSA's records are lines 96
// and 100, DesconverteEstadoSA's lines 156 and 160, and binaryen inlines each into its one caller.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeralsa.h"

#include <format>

#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

CConversorEstadoGeralSA::TEntidade CConversorEstadoGeralSA::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_estadoSA(ConverteEstadoSA(dado.GetEstadoSA()));
    entidade.set_atualizacaoBloqueada(dado.GetAtualizacaoBloqueada());
    entidade.set_dadosSecao().set_municipio(dado.GetMunicipio());
    entidade.set_dadosSecao().set_zona(dado.GetZona());
    entidade.set_dadosSecao().set_secao(dado.GetSecao());
    return entidade;
}

CConversorEstadoGeralSA::TDado CConversorEstadoGeralSA::DoDesconverte(const TEntidade& entidade) const
{
    const EEstadoSA estado = DesconverteEstadoSA(entidade.get_estadoSA());
    const auto& secao = entidade.get_dadosSecao();
    return TDado(estado, entidade.get_atualizacaoBloqueada(), secao.get_municipio().getValue(),
                 secao.get_zona().getValue(), secao.get_secao().getValue());
}

// (original lines 31-45: content not recovered)
#line 46
ModuloEstadoGeralSA::EstadoSA CConversorEstadoGeralSA::ConverteEstadoSA(const EEstadoSA estado) const
{
    switch (estado) {
        case eSAInicial:
            return ModuloEstadoGeralSA::EstadoSA::inicial;
        case eSAArvoreRaizPreparada:
            return ModuloEstadoGeralSA::EstadoSA::arvoreraizpreparada;
        case eSAPreparada:
            return ModuloEstadoGeralSA::EstadoSA::preparada;
        case eSAImprimirZESecao:
            return ModuloEstadoGeralSA::EstadoSA::imprimirZEsecao;
        case eSAIniciarApuracao:
            return ModuloEstadoGeralSA::EstadoSA::iniciarapuracao;
        case eSAApurarMajoritaria:
            return ModuloEstadoGeralSA::EstadoSA::apurarmajoritaria;
        case eSAMajoritariaCompleta:
            return ModuloEstadoGeralSA::EstadoSA::majoritariacompleta;
        case eSAMajoritariaEncerrada:
            return ModuloEstadoGeralSA::EstadoSA::majoritariaencerrada;
        case eSAApurarProporcional:
            return ModuloEstadoGeralSA::EstadoSA::apurarproporcional;
        case eSAProporcionalCompleta:
            return ModuloEstadoGeralSA::EstadoSA::proporcionalcompleta;
        case eSAProporcionalEncerrada:
            return ModuloEstadoGeralSA::EstadoSA::proporcionalencerrada;
        case eSABUIniciaCargo:
            return ModuloEstadoGeralSA::EstadoSA::buiniciacargo;
        case eSABUProporcionalPedePartido:
            return ModuloEstadoGeralSA::EstadoSA::buproporcionalpedepartido;
        case eSABUProporcionalPedeCandidato:
            return ModuloEstadoGeralSA::EstadoSA::buproporcionalpedecandidato;
        case eSABUMajoritariaPedeCandidato:
            return ModuloEstadoGeralSA::EstadoSA::bumajoritariapedecandidato;
        case eSABURegistraBUNoRDV:
            return ModuloEstadoGeralSA::EstadoSA::buregistrabunordv;
        case eSAPosicionarMista:
            return ModuloEstadoGeralSA::EstadoSA::posicionarmista;
        case eSAGravarBU:
            return ModuloEstadoGeralSA::EstadoSA::gravarbu;
        case eSAImprimirBU:
            return ModuloEstadoGeralSA::EstadoSA::imprimirbu;
        case eSAGravaResultado:
            return ModuloEstadoGeralSA::EstadoSA::gravaresultado;
        case eSACopiaResultadoMR:
            return ModuloEstadoGeralSA::EstadoSA::copiaresultadomr;
        case eSAImprimirAdicionalBU:
            return ModuloEstadoGeralSA::EstadoSA::imprimiradicionalbu;
        case eSAEncerrada:
            return ModuloEstadoGeralSA::EstadoSA::encerrada;
        case eSAUltimoID:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7925,
                                     std::format("Valor inválido para EEstadoSA: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7926,
                             std::format("Valor inválido para EEstadoSA: {}", estado));
}


EEstadoSA CConversorEstadoGeralSA::DesconverteEstadoSA(const ModuloEstadoGeralSA::EstadoSA& estado) const
{
    switch (estado) {
        case ModuloEstadoGeralSA::EstadoSA::inicial:
            return eSAInicial;
        case ModuloEstadoGeralSA::EstadoSA::arvoreraizpreparada:
            return eSAArvoreRaizPreparada;
        case ModuloEstadoGeralSA::EstadoSA::preparada:
            return eSAPreparada;
        case ModuloEstadoGeralSA::EstadoSA::imprimirZEsecao:
            return eSAImprimirZESecao;
        case ModuloEstadoGeralSA::EstadoSA::iniciarapuracao:
            return eSAIniciarApuracao;
        case ModuloEstadoGeralSA::EstadoSA::apurarmajoritaria:
            return eSAApurarMajoritaria;
        case ModuloEstadoGeralSA::EstadoSA::majoritariacompleta:
            return eSAMajoritariaCompleta;
        case ModuloEstadoGeralSA::EstadoSA::majoritariaencerrada:
            return eSAMajoritariaEncerrada;
        case ModuloEstadoGeralSA::EstadoSA::apurarproporcional:
            return eSAApurarProporcional;
        case ModuloEstadoGeralSA::EstadoSA::proporcionalcompleta:
            return eSAProporcionalCompleta;
        case ModuloEstadoGeralSA::EstadoSA::proporcionalencerrada:
            return eSAProporcionalEncerrada;
        case ModuloEstadoGeralSA::EstadoSA::buiniciacargo:
            return eSABUIniciaCargo;
        case ModuloEstadoGeralSA::EstadoSA::buproporcionalpedepartido:
            return eSABUProporcionalPedePartido;
        case ModuloEstadoGeralSA::EstadoSA::buproporcionalpedecandidato:
            return eSABUProporcionalPedeCandidato;
        case ModuloEstadoGeralSA::EstadoSA::bumajoritariapedecandidato:
            return eSABUMajoritariaPedeCandidato;
        case ModuloEstadoGeralSA::EstadoSA::buregistrabunordv:
            return eSABURegistraBUNoRDV;
        case ModuloEstadoGeralSA::EstadoSA::posicionarmista:
            return eSAPosicionarMista;
        case ModuloEstadoGeralSA::EstadoSA::gravarbu:
            return eSAGravarBU;
        case ModuloEstadoGeralSA::EstadoSA::imprimirbu:
            return eSAImprimirBU;
        case ModuloEstadoGeralSA::EstadoSA::gravaresultado:
            return eSAGravaResultado;
        case ModuloEstadoGeralSA::EstadoSA::copiaresultadomr:
            return eSACopiaResultadoMR;
        case ModuloEstadoGeralSA::EstadoSA::imprimiradicionalbu:
            return eSAImprimirAdicionalBU;
        case ModuloEstadoGeralSA::EstadoSA::encerrada:
            return eSAEncerrada;
        case ModuloEstadoGeralSA::EstadoSA::unknownEnumeration_:
        case ModuloEstadoGeralSA::EstadoSA::ultimoid:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7927,
                                     std::format("Valor inválido para EstadoSA: {}", estado));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7928,
                             std::format("Valor inválido para EstadoSA: {}", estado));
}

} // namespace comum::asn

// <stubs>
// f10089 · 20 B · unmatched · placement: link order · name unknown
// void f10089(i32, i32) { ... }
// </stubs>
