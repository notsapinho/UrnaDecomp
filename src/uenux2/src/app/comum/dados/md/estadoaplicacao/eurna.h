#pragma once

// The urna's state enums the comum::md::estadoaplicacao classes and their converters hold. The records print them
// unqualified (const EUrnaModelo, const EUrnaTipo, const EUrnaAplicativo, const EEstadoSA), and app/comum/eurnafase.h
// keeps EUrnaFase in comum, so the scope is chosen, like this file's path. Every enumerator's value comes from the bodies
// named below it; every enumerator's name is chosen, from the generated ASN.1 enumerator of the same position.

#include <format>

#include "app/comum/eurnafase.h"

namespace comum {

// CConversorDadoCarga::ConverteTipoUrna (target fn 5693): 48 to 52, one per ModuloEstadoGeralUrna::TipoUrnaOperacao.
enum EUrnaTipo {
    eUrnaSemTipo = 48,
    eUrnaVota = 49,
    eUrnaContingencia = 50,
    eUrnaContingenciaVota = 51,
    eUrnaContingenciaVotaRecupera = 52,
};

// The values fn 11402 gives the model; CDadoCarga::ValidaModelo (target fn 5633) allows the range between the ends.
enum EUrnaModelo {
    eModeloUE2013 = 2013,
    eModeloUE2015 = 2015,
    eModeloUE2020 = 2020,
    eModeloUE2022 = 2022,
};

// CConversorEstadoGeralGap::ConverteUrnaAplicativo (target fn 5689): 0 to 14 are ModuloEstadoGeralGap::UrnaAplicativo's
// values, 15 is the end marker it refuses.
enum EUrnaAplicativo {
    eApVotaTreinaEleitor1,
    eApVotaTreinaEleitor2,
    eApVotaTreinaMesario1,
    eApVotaTreinaMesario2,
    eApVotaSimula1,
    eApVotaSimula2,
    eApVotaOficial1,
    eApVotaOficial2,
    eApApuracaoTreina1,
    eApApuracaoTreina2,
    eApApuracaoSimula1,
    eApApuracaoSimula2,
    eApApuracaoOficial1,
    eApApuracaoOficial2,
    eApSemAplicativo,
    eApUltimoID,
};

// CConversorEstadoGeralSA::ConverteEstadoSA (target fn 11392): 49 to 71 are ModuloEstadoGeralSA::EstadoSA's values 0 to
// 22, 72 is the end marker it refuses.
enum EEstadoSA {
    eSAInicial = 49,
    eSAArvoreRaizPreparada,
    eSAPreparada,
    eSAImprimirZESecao,
    eSAIniciarApuracao,
    eSAApurarMajoritaria,
    eSAMajoritariaCompleta,
    eSAMajoritariaEncerrada,
    eSAApurarProporcional,
    eSAProporcionalCompleta,
    eSAProporcionalEncerrada,
    eSABUIniciaCargo,
    eSABUProporcionalPedePartido,
    eSABUProporcionalPedeCandidato,
    eSABUMajoritariaPedeCandidato,
    eSABURegistraBUNoRDV,
    eSAPosicionarMista,
    eSAGravarBU,
    eSAImprimirBU,
    eSAGravaResultado,
    eSACopiaResultadoMR,
    eSAImprimirAdicionalBU,
    eSAEncerrada,
    eSAUltimoID,
};

} // namespace comum

namespace comum {

// An enum formats as an unsigned value: the 31 table slots of target fn 536 hold one handle body, which tests `>= 128`
// unsigned for the char presentation, so formatter<unsigned int>, as ecourna/app/dados/tiposbasicos.hpp writes it for one
// enum. This base and the explicit specializations below are chosen: a template constrained on std::is_enum_v gives the
// same bodies (measured on EUrnaModelo and EUrnaFase), and an explicit specialization stays valid beside such a template.
// EUrnaFase's stays here, not in app/comum/asn/util.h's template, since this tree's TUs do not include that header; with
// it, which is what sends the enum through fn 536, `: int` and `: unsigned int` give the same cdadocarga.cpp object.
// CDadoCarga::GetFaseChar (target fn 2253) gives 'o', 's' and 't' for its 49, 50 and 51, and CGravadorUtil::ConverteFase
// (fn 2274) takes those three chars back.
struct SFormatoEnum : std::formatter<unsigned int> {
    template <typename E, typename FormatContext>
    auto format(E valor, FormatContext& contexto) const
    {
        return std::formatter<unsigned int>::format(static_cast<unsigned int>(valor), contexto);
    }
};

} // namespace comum

template <>
struct std::formatter<comum::EUrnaFase> : comum::SFormatoEnum {};
template <>
struct std::formatter<comum::EUrnaModelo> : comum::SFormatoEnum {};
template <>
struct std::formatter<comum::EUrnaAplicativo> : comum::SFormatoEnum {};
template <>
struct std::formatter<comum::EEstadoSA> : comum::SFormatoEnum {};
