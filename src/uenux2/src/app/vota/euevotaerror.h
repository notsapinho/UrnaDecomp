#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

// The error class's RTTI, CBaseError<vota::EUeVotaError, SErrorLimits{9300, 9500}>, gives the enum's name, its
// namespace and its limits. This file's path and the CUeVotaError alias name are chosen, after api/util/eueutilerror.h
// and its CUeUtilError: no record names the file and no evidence names the alias.

namespace vota {

enum EUeVotaError {
    // the value is the code vota::IQRCodeBUDS::IQRCodeBUDS (inlined into target fn 1956) throws; the name is chosen
    // from its message, "Vetor de partes vazio": no evidence names it
    EUE_VOTA_VETOR_PARTES_VAZIO = 9372,
    // the value is the code vota::IIniciaJustificativa's constructor (target fn 3624) throws; the name is chosen from
    // its message, "Confirmação de justificativa nula": no evidence names it
    EUE_VOTA_CONFIRMACAO_JUSTIFICATIVA_NULA = 9396,
    // the value is the code vota::CControlaReconhecimento::AvancaTentativa (target fn 5406) throws; the name is chosen
    // from its message, "Limite de tentativas atingido.": no evidence names it
    EUE_VOTA_LIMITE_TENTATIVAS_ATINGIDO = 9397,
    // the values are the codes CInformacaoThreadOperador's four getters throw (target fns 10562, 10561, 10560, 10559);
    // the names are chosen from their messages and their getters, "Identidade não registrada" and "Tipo de identidade
    // não registrado": no evidence names them
    EUE_VOTA_IDENTIDADE_DIGITADA_NAO_REGISTRADA = 9401,
    EUE_VOTA_TIPO_IDENTIDADE_NAO_REGISTRADO = 9402,
    EUE_VOTA_IDENTIDADE_ELEITOR_NAO_REGISTRADA = 9403,
    EUE_VOTA_IDENTIDADE_PRINCIPAL_NAO_REGISTRADA = 9404,
};

using CUeVotaError = ecourna::api::exception::CBaseError<EUeVotaError, ecourna::api::exception::SErrorLimits{9300, 9500}>;

} // namespace vota
