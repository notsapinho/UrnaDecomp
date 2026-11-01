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
    // the code api::CDirReader's constructor throws (cdirreader.cpp); the name is chosen from its message, "Não foi
    // possível ler o diretório ": no evidence names it
    EUE_UTIL_FALHA_LER_DIRETORIO = 7009,
    EUE_UTIL_DIRETORIO_NAO_ABERTO = 7010,
    // 7013 to 7015: the codes api::CGenericTags::insert throws (cgenerictags.cpp); each name is chosen from its message
    // and what the throw tests (the tag's size, a tag already in the map, a length-field size outside 1 to 4): no
    // evidence names them
    EUE_UTIL_TAG_TAMANHO_INVALIDO = 7013,
    EUE_UTIL_TAG_JA_MAPEADA = 7014,
    EUE_UTIL_TAG_TAMANHO_CAMPO_INVALIDO = 7015,
    EUE_UTIL_TAG_NAO_MAPEADA = 7016,
    // 7017 to 7019: the codes api::CGenericTags::EncodeTLV and AppendTLV throw (cgenerictags.cpp); each name is chosen
    // from its message and the function that throws it: no evidence names them
    EUE_UTIL_TLV_TAG_TAMANHO_INVALIDO = 7017,
    EUE_UTIL_TLV_LIMITE_EXCEDIDO = 7018,
    EUE_UTIL_TLV_ANEXA_TAG_TAMANHO_INVALIDO = 7019,
    // the code api::CSynchronizer::CreateInst throws (csynchronizer.cpp); the name is chosen from its message, "Instância já
    // criada": no evidence names it
    EUE_UTIL_SINCRONIZADOR_JA_CRIADO = 7030,
    // 7031 and 7069: the codes api::ExistResource and api::CSystem::ZeroFill throw (csystem.cpp); each name is chosen
    // from its message, "Falha ao validar a existência do recurso" and "Falha ao abrir arquivo": no evidence names them
    EUE_UTIL_FALHA_VALIDAR_RECURSO = 7031,
    EUE_UTIL_FALHA_OBTER_TAMANHO_ARQUIVO = 7038,
    // 7041 to 7048 and 7058: the codes api::CSystem::CopyFile and Rename throw (csystem.cpp); each name is chosen from
    // its message: no evidence names them. 7041's throw (record at line 390, "O arquivo de destino [{}] já existe") is
    // folded away with the argument it tests, so its value is chosen too, the one before 7042 to 7048, which the file's
    // next throws pass in line order
    EUE_UTIL_ARQUIVO_DESTINO_EXISTENTE = 7041,
    EUE_UTIL_FALHA_LER_ARQUIVO_ORIGEM = 7042,
    EUE_UTIL_FALHA_CRIAR_ARQUIVO_DESTINO = 7043,
    EUE_UTIL_FALHA_COPIAR_ARQUIVO = 7044,
    EUE_UTIL_FALHA_OBTER_INFORMACOES_ARQUIVO = 7045,
    EUE_UTIL_FALHA_ALTERAR_HORA_ARQUIVO = 7046,
    EUE_UTIL_FALHA_ALTERAR_DONO_ARQUIVO = 7047,
    EUE_UTIL_FALHA_ALTERAR_PERMISSOES_ARQUIVO = 7048,
    EUE_UTIL_FALHA_RENOMEAR = 7058,
    EUE_UTIL_FALHA_ABRIR_ARQUIVO = 7069,
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
