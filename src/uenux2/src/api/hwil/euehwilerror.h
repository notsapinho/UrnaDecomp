#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// Recovered: the typeinfo of ecourna::api::exception::CBaseError<api::EUeHwilError, SErrorLimits{5150, 5950}> names the
// enumeration, its namespace and its limits (ledger/classes.json). The file's path is chosen, beside api/hwil/ipower.h
// and on the pattern of api/io/eueioerror.h and api/gui/eueguierror.h: no record names it.
enum EUeHwilError {
    // the values are the codes api::IPower's defaults throw (target fns 8105, 8098, 8091, 8083 and 8074); the names are
    // chosen from the member that throws each and its message, "Not supported": no evidence names them
    // the value is the code IInput::GetKey throws (its record's functions); the name is chosen from its message, "IInput -
    // Nao havia um caractere disponivel"
    EUE_HWIL_TECLA_INDISPONIVEL = 5170,
    EUE_HWIL_BATINTMAXSOCVALUE_NAO_SUPORTADO = 5172,
    EUE_HWIL_SETBATINTMAXSOCVALUE_NAO_SUPORTADO = 5173,
    EUE_HWIL_BATINTSTORAGEMODE_NAO_SUPORTADO = 5174,
    EUE_HWIL_ENABLEBATINTSTORAGEMODE_NAO_SUPORTADO = 5175,
    EUE_HWIL_DISABLEBATINTSTORAGEMODE_NAO_SUPORTADO = 5176,
};

using CUeHwilError = ecourna::api::exception::CBaseError<EUeHwilError, ecourna::api::exception::SErrorLimits{5150, 5950}>;

} // namespace api
