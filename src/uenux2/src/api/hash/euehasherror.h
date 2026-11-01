#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// api::EUeHashError, SErrorLimits{5100, 5150}: the typeinfo of CBaseError<api::EUeHashError, ...> gives the enum's name,
// namespace and limits. The values are the codes the two throws of api/hash/chasharquivo.cpp pass (fn 5364). Each
// enumerator's name is chosen from its message: no evidence names one. The path, beside the classes that throw it, is
// chosen too.
enum EUeHashError {
    EUE_HASH_NOME_INVALIDO = 5100,
    EUE_HASH_HASH_INVALIDO = 5101,
};

using CUeHashError = ecourna::api::exception::CBaseError<EUeHashError, ecourna::api::exception::SErrorLimits{5100, 5150}>;

} // namespace api
