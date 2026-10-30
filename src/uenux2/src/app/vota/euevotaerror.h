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
};

using CUeVotaError = ecourna::api::exception::CBaseError<EUeVotaError, ecourna::api::exception::SErrorLimits{9300, 9500}>;

} // namespace vota
