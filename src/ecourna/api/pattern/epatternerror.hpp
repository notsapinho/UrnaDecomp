#pragma once
#include "ecourna/api/exception/cbaseerror.hpp"

namespace ecourna::api::pattern {

enum EPatternError {
    EPE_VALOR_INVALIDO = 1300,
    EPE_INSTANCIA_NAO_CRIADA = 1301, // the name is chosen from its message: no evidence names it
    EPE_SINGLETON_NAO_CRIADO = 1303, // the name is chosen from its message: no evidence names it
    // the code a singleton's CreateInst throws when the instance exists (vota::CTelasVota's, inlined into target fn
    // 7787, record ctelasvota.cpp:3435, "CTelasVota - instancia ja criada"); the name is chosen from its message
    EPE_SINGLETON_JA_CRIADO = 1304,
};

using CPatternError = exception::CBaseError<EPatternError, exception::SErrorLimits{1300, 1325}>;

} // namespace ecourna::api::pattern
