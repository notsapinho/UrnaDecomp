#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeIoError {
    // the codes api::CFileASN's readers throw (ReadFromFile, records cfileasn.h 48, 60 and 78, and
    // DecodeObjectFunction, 135 and 143, all held by target fn 3791); chosen from the messages
    EUE_IO_ARQUIVO_NAO_ABERTO = 5950,
    EUE_IO_ARQUIVO_MUITO_GRANDE = 5951,
    EUE_IO_ARQUIVO_NAO_EXISTE = 5952,
    EUE_IO_CONTEUDO_NAO_DECODIFICADO = 5953,
    EUE_IO_CONTEUDO_INVALIDO = 5954,
    // the codes api::CFileASN::CodeObjectFunction throws (target fn 2927, records cfileasn.h 161 and 171); chosen from
    // the messages
    EUE_IO_OBJETO_INVALIDO = 5955,
    EUE_IO_OBJETO_NAO_CODIFICADO = 5956,
    // the values are the codes api::CFileSeeder's members throw (target fns 11433, 11432, 11431 twice and 11430); no
    // evidence names them: they are chosen from the messages, and 5959's and 5960's (one message) from each test
    EUE_IO_SEEDER_SEM_BYTES = 5957,
    EUE_IO_SEEDER_FALHA_LER = 5958,
    EUE_IO_SEEDER_POSICAO_INVALIDA = 5959,   // seek: the position is past the size
    EUE_IO_SEEDER_FALHA_REPOSICIONAR = 5960, // seek: CFile::Seek failed
    EUE_IO_SEEDER_SALTO_INVALIDO = 5961,
    // the codes api::CPartialFileASN's readers throw (ReadFromFile, record cpartialfileasn.h 182, and
    // DecodeObjectFunction, 277 and 285, all held by target fn 11523); chosen from the messages and the class
    EUE_IO_ARQUIVO_PARCIAL_NAO_ABERTO = 5963,
    EUE_IO_CONTEUDO_PARCIAL_NAO_DECODIFICADO = 5968,
    EUE_IO_CONTEUDO_PARCIAL_INVALIDO = 5969,
    // the codes of api::CDataMap's four throws (target fns 2919, 3892, 5725 and 5377, 5378); chosen from the messages
    EUE_IO_REGISTRO_CORRENTE_INVALIDO = 5976,
    EUE_IO_OPERACAO_INVALIDA = 5977,
    EUE_IO_REGISTRO_DUPLICADO = 5978,
    EUE_IO_REGISTRO_NAO_ENCONTRADO = 5979,
    // the codes of api::CEncryptedFile::Load (target fn 3653), which builds 5989, 5990 and 5993 without throwing them;
    // chosen from the messages (5987's is Save's message too, under its own code)
    EUE_IO_LOAD_NOME_ARQUIVO_VAZIO = 5987,
    EUE_IO_ARQUIVO_INEXISTENTE = 5988,
    EUE_IO_TAMANHO_ARQUIVO_INVALIDO = 5989,
    EUE_IO_FALHA_LEITURA_ARQUIVO = 5990,
    EUE_IO_PADDING_INVALIDO = 5991,
    EUE_IO_PADDING_EXCESSIVO = 5992,
    EUE_IO_PADDING_SECUNDARIO_INVALIDO = 5993,
    // the code api::CEncryptedFile::Save throws (target fn 2767); chosen from its message, "Nome de arquivo vazio"
    EUE_IO_NOME_ARQUIVO_VAZIO = 5994,
    // the codes of api::CEncryptedFile::MemWrite and MemRead (held by target fns 2766 and 3652); chosen from the messages
    // and the member that throws them
    EUE_IO_MEMWRITE_TAMANHO_INVALIDO = 5996,
    EUE_IO_MEMWRITE_BUFFER_INVALIDO = 5997,
    EUE_IO_MEMREAD_TAMANHO_INVALIDO = 5998,
    EUE_IO_MEMREAD_BUFFER_INVALIDO = 5999,
    EUE_IO_MEMREAD_NADA_PARA_LER = 6000,
    EUE_IO_NOME_CHAVE_MODIFICADO = 6005,
    // the codes of api::CIniSection::operator= (record cinisection.cpp 36) and api::CIniStrings::ParseKeyLine (records
    // cinistrings.cpp 183 and 187), all held by target fn 5480; chosen from the messages
    EUE_IO_NOME_SECAO_MODIFICADO = 6007,
    EUE_IO_LINHA_INVALIDA = 6009,
    EUE_IO_NOME_CHAVE_INVALIDO = 6010,
};

using CUeIoError = ecourna::api::exception::CBaseError<EUeIoError, ecourna::api::exception::SErrorLimits{5950, 6150}>;

} // namespace api
