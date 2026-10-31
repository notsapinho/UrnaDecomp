#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// The enum's name, namespace and limits are the RTTI's: the throws of src/api/uelog/cescritorlog.cpp (target fns 10260
// and 10262) throw ecourna::api::exception::CBaseError<api::EUeUeLogError, SErrorLimits{6950, 7000}> (typeinfo
// 1599588). This header's path is chosen, beside the file that throws.
enum EUeUeLogError {
    // the value is the code api::confereAppValida throws (record cescritorlog.cpp 28:15, inlined into fn 10260); the
    // name is chosen from its message, "{} - O código da aplicação deve ser menor que {} [{}]": no evidence names it
    EUE_UELOG_APLICACAO_INVALIDA = 6950,
    // the values are the codes api::CEscritorLog::fazOperacao (target fn 10262) throws; the names are chosen from its
    // messages, "Não existe nenhuma operação com número menor que {} [{}]" and "... maior que {} [{}]": no evidence names
    // them
    EUE_UELOG_OPERACAO_MENOR = 6951,
    EUE_UELOG_OPERACAO_MAIOR = 6952,
};

using CUeUeLogError = ecourna::api::exception::CBaseError<EUeUeLogError, ecourna::api::exception::SErrorLimits{6950, 7000}>;

} // namespace api
