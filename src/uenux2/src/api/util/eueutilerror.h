#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeUtilError {
    EUE_UTIL_DIRETORIO_NAO_ABERTO = 7010,
    EUE_UTIL_TAG_NAO_MAPEADA = 7016,
    EUE_UTIL_FALHA_OBTER_TAMANHO_ARQUIVO = 7038,
    EUE_UTIL_FALHA_TRUNCAR_ARQUIVO = 7070,
    EUE_UTIL_TICK_TEMPO_INVALIDO = 7072,
    EUE_UTIL_TICK_NAO_EXISTE_PARAR = 7074,
    EUE_UTIL_TICK_NAO_EXISTE_INICIAR = 7075,
    EUE_UTIL_TICK_SEM_ID_DISPONIVEL = 7077,
    EUE_UTIL_HORA_INVALIDA = 7079,
    EUE_UTIL_HORA_OVERFLOW = 7081,
    EUE_UTIL_HORA_UNDERFLOW = 7082,
    EUE_UTIL_TEMPO_EXCESSIVO = 7083,
};

using CUeUtilError = ecourna::api::exception::CBaseError<EUeUtilError, ecourna::api::exception::SErrorLimits{7000, 7200}>;

} // namespace api
