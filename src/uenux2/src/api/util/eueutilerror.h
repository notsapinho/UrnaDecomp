#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeUtilError {
    // 7001 to 7008: the codes api::CDate's and api::CDateTime's throws pass (cdate.cpp, cdatetime.cpp); each name is
    // chosen from its message and what the throw tests: no evidence names them
    EUE_UTIL_DATA_INVALIDA = 7001,
    EUE_UTIL_DATA_NAO_CONVERTIDA = 7002,
    EUE_UTIL_DIA_SEMANA_INVALIDO = 7003,
    EUE_UTIL_DATAHORA_INVALIDA = 7005,
    EUE_UTIL_DATAHORA_NAO_CONVERTIDA = 7006,
    EUE_UTIL_TIMESTAMP_INVALIDO = 7008,
    EUE_UTIL_DIRETORIO_NAO_ABERTO = 7010,
    EUE_UTIL_TAG_NAO_MAPEADA = 7016,
    EUE_UTIL_FALHA_OBTER_TAMANHO_ARQUIVO = 7038,
    EUE_UTIL_FALHA_TRUNCAR_ARQUIVO = 7070,
    EUE_UTIL_TICK_TEMPO_INVALIDO = 7072,
    EUE_UTIL_TICK_NAO_EXISTE_PARAR = 7074,
    EUE_UTIL_TICK_NAO_EXISTE_INICIAR = 7075,
    EUE_UTIL_TICK_SEM_ID_DISPONIVEL = 7077,
    EUE_UTIL_HORA_INVALIDA = 7079,
    // the value is the code api::EncodeTime(const std::string &) throws (inlined into the CTime constructor from a
    // string, target fn 3643); the name is chosen from its message, "Hora inválida", as 7079's, and its string
    // argument: no evidence names it
    EUE_UTIL_HORA_TEXTO_INVALIDA = 7080,
    EUE_UTIL_HORA_OVERFLOW = 7081,
    EUE_UTIL_HORA_UNDERFLOW = 7082,
    EUE_UTIL_TEMPO_EXCESSIVO = 7083,
    EUE_UTIL_SYSTEMDATETIME_RECRIADO = 7084, // the name is chosen from its message: no evidence names it
    EUE_UTIL_TIMERSCHEDULER_RECRIADO = 7085, // the name is chosen from its message: no evidence names it
};

using CUeUtilError = ecourna::api::exception::CBaseError<EUeUtilError, ecourna::api::exception::SErrorLimits{7000, 7200}>;

} // namespace api
