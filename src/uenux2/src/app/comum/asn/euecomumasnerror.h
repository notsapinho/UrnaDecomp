#pragma once

// comum::EUeComumAsnError, SErrorLimits{7650, 7750}: the typeinfo of CBaseError<comum::EUeComumAsnError, ...> (1528108)
// gives the enum's name, namespace and limits, and the target's calls of the constructor's thunk, fn 255, give the
// codes. No record names this header: its path is chosen, beside the files that throw the error. No evidence names an
// enumerator: each name is chosen from the message its throw builds. A code no written function throws has no
// enumerator yet.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumAsnError {
    EUE_COMUM_ASN_TIPO_ABRANGENCIA_INVALIDO = 7650,
    EUE_COMUM_ASN_TIPO_CABECALHO_INVALIDO = 7651,
    EUE_COMUM_ASN_TIPO_ID_CABECALHO_INVALIDO = 7652,
    EUE_COMUM_ASN_ENTIDADE_ESTADO_INVALIDO = 7653,
    EUE_COMUM_ASN_ENTIDADE_INVALIDA = 7654,
    EUE_COMUM_ASN_DOCONVERTE_NAO_IMPLEMENTADO = 7655,
    EUE_COMUM_ASN_DODESCONVERTE_NAO_IMPLEMENTADO = 7656,
    EUE_COMUM_ASN_ENTIDADE_BIOMETRIA_INVALIDA = 7658,
    EUE_COMUM_ASN_DOCONVERTE_BIOMETRIA_NAO_IMPLEMENTADO = 7659,
    // the code of IConversorParcialASN::Desconverte (record iconversorparcialasn.h:52, held by target fn 11523), chosen
    // from its message, "Entidade deixada em estado inválido: {}"
    EUE_COMUM_ASN_ENTIDADE_PARCIAL_ESTADO_INVALIDO = 7665,
    EUE_COMUM_ASN_LEITOR_SEEK = 7669,
    EUE_COMUM_ASN_LEITOR_LEITURA = 7670,
    EUE_COMUM_ASN_FORMATO_DATA_INVALIDO = 7671,
    EUE_COMUM_ASN_TIPO_ID_INVALIDO = 7673,
    EUE_COMUM_ASN_FASE_INVALIDA_CONVERTE = 7674,
    EUE_COMUM_ASN_FASE_INVALIDA_DESCONVERTE = 7675,
    EUE_COMUM_ASN_TIPO_PACOTE_INVALIDO_CONVERTE = 7678,
    EUE_COMUM_ASN_TIPO_PACOTE_INVALIDO_DESCONVERTE = 7679,
    EUE_COMUM_ASN_TIPO_ID_ELEITORAL_INVALIDO = 7680,
    EUE_COMUM_ASN_SISTEMA_INVALIDO_CONVERTE = 7681,
    EUE_COMUM_ASN_SISTEMA_INVALIDO_DESCONVERTE = 7682,
    EUE_COMUM_ASN_SEXO_INVALIDO = 7684,
    EUE_COMUM_ASN_ABRANGENCIA_INVALIDA_CONVERTE = 7685,
    EUE_COMUM_ASN_ABRANGENCIA_INVALIDA = 7686,
    EUE_COMUM_ASN_TIPO_LOCAL_INVALIDO_CONVERTE = 7687,
    EUE_COMUM_ASN_TIPO_LOCAL_INVALIDO_DESCONVERTE = 7688,
    EUE_COMUM_ASN_TURNO_INVALIDO_CONVERTE = 7689,
    EUE_COMUM_ASN_TURNO_INVALIDO_DESCONVERTE = 7690,
    // the codes of legravaentidade.h's LeEntidadeEm (records :92 and :98, held by target fn 3755 for the candidates'
    // photos); its messages are LeEntidadeBiometria's, so the names are chosen from them and from the function
    EUE_COMUM_ASN_LEITOR_EM_SEEK = 7667,
    EUE_COMUM_ASN_LEITOR_EM_LEITURA = 7668,
};

using CUeComumAsnError =
    ecourna::api::exception::CBaseError<EUeComumAsnError, ecourna::api::exception::SErrorLimits{7650, 7750}>;

} // namespace comum
