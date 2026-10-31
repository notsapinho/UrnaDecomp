#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUePatternError {
    EUE_PATTERN_INSTANCIA_NAO_CRIADA = 6754, // the name is chosen from its message: no evidence names it
    EUE_PATTERN_INSTANCIA_INCOMPATIVEL = 6755, // the name is chosen from its message: no evidence names it
    EUE_PATTERN_INSTANCIA_JA_CRIADA = 6756, // the name is chosen from its message: no evidence names it
};

using CUePatternError = ecourna::api::exception::CBaseError<EUePatternError, ecourna::api::exception::SErrorLimits{6750, 6800}>;

} // namespace api
