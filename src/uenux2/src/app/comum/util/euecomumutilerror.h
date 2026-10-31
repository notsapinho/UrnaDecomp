#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// The error codes of app/comum/util. The enum's name, its namespace and its limits are the target's: the typeinfo of
// CBaseError<comum::EUeComumUtilError, SErrorLimits{9150, 9200}> @1600712. This header's path is chosen, beside the one
// file that throws it so far. The value is the code fn 1898 passes, and its name is chosen from the message: no
// evidence names an enumerator.
enum EUeComumUtilError {
    // comum::util::CMonitoraAlimentacao::CreateInst, "Instancia ja criada" (spelled with its accents in the source).
    EUE_COMUM_UTIL_INSTANCIA_JA_CRIADA = 9156,
};

using CUeComumUtilError = ecourna::api::exception::CBaseError<EUeComumUtilError, ecourna::api::exception::SErrorLimits{9150, 9200}>;

} // namespace comum
