#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeIoError {
    // the values are the codes api::CFileSeeder's members throw (target fns 11433, 11432, 11431 twice and 11430); no
    // evidence names them: they are chosen from the messages, and 5959's and 5960's (one message) from each test
    EUE_IO_SEEDER_SEM_BYTES = 5957,
    EUE_IO_SEEDER_FALHA_LER = 5958,
    EUE_IO_SEEDER_POSICAO_INVALIDA = 5959,   // seek: the position is past the size
    EUE_IO_SEEDER_FALHA_REPOSICIONAR = 5960, // seek: CFile::Seek failed
    EUE_IO_SEEDER_SALTO_INVALIDO = 5961,
    EUE_IO_NOME_CHAVE_MODIFICADO = 6005,
};

using CUeIoError = ecourna::api::exception::CBaseError<EUeIoError, ecourna::api::exception::SErrorLimits{5950, 6150}>;

} // namespace api
