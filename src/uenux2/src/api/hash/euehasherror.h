#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// api::EUeHashError, SErrorLimits{5100, 5150}: the typeinfo of CBaseError<api::EUeHashError, ...> gives the enum's
// name, namespace and limits. The values are the codes the throws pass: 5100 and 5101 those of
// api/hash/chasharquivo.cpp (fn 5364), 5102 chashdiretorio.cpp:41's and 5103 cmontadorhash.cpp:121's (both in fn 5360).
// Each enumerator's name is chosen from its message: no evidence names one. The path, beside the classes that throw it,
// is chosen too.
enum EUeHashError {
    EUE_HASH_NOME_INVALIDO = 5100,
    EUE_HASH_HASH_INVALIDO = 5101,
    EUE_HASH_DIRETORIO_NOME_INVALIDO = 5102,
    EUE_HASH_DIRETORIO_NAO_ABERTO = 5103,
};

using CUeHashError = ecourna::api::exception::CBaseError<EUeHashError, ecourna::api::exception::SErrorLimits{5100, 5150}>;

} // namespace api
