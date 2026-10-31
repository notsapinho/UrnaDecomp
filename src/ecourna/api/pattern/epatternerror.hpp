#pragma once
#include "ecourna/api/exception/cbaseerror.hpp"

namespace ecourna::api::pattern {

enum EPatternError {
    EPE_VALOR_INVALIDO = 1300,
    EPE_INSTANCIA_NAO_CRIADA = 1301, // the name is chosen from its message: no evidence names it
    EPE_SINGLETON_NAO_CRIADO = 1303, // the name is chosen from its message: no evidence names it
};

using CPatternError = exception::CBaseError<EPatternError, exception::SErrorLimits{1300, 1325}>;

} // namespace ecourna::api::pattern
