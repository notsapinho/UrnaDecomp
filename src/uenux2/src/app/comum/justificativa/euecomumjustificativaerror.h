#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// comum::EUeComumJustificativaError, SErrorLimits{8800, 8850}: the typeinfo of CBaseError<comum::EUeComumJustificativaError,
// ...> gives the enum's name, namespace and limits. The values are the codes the throws pass: the two of
// app/comum/justificativa/dao/cjustificadordao.cpp and the three of cjustificador.cpp (held by fns 10590 and 11475).
// Each enumerator's name is chosen from its message: no evidence names one. The path, in the directory of the classes
// that throw it, is chosen too.
enum EUeComumJustificativaError {
    // CJustificador::Justifica's ("Já havia justificativa para o título") and SaveCurrentInternal's ("Não há dados a
    // serem salvos na MI"), both held by fn 10590; the names are chosen from those messages.
    EUE_COMUM_JUSTIFICATIVA_JA_JUSTIFICADO = 8800,
    EUE_COMUM_JUSTIFICATIVA_SEM_DADOS = 8801,
    // CJustificadorDadoTitulo::Text's (fn 11475, "Justificativa inválida"); the name is chosen from that message.
    EUE_COMUM_JUSTIFICATIVA_INVALIDA = 8802,
    EUE_COMUM_JUSTIFICATIVA_DAO_EXCLUSAO_NAO_ESPERADA = 8804,
    EUE_COMUM_JUSTIFICATIVA_DAO_ATUALIZACAO_NAO_ESPERADA = 8805,
};

using CUeComumJustificativaError =
    ecourna::api::exception::CBaseError<EUeComumJustificativaError, ecourna::api::exception::SErrorLimits{8800, 8850}>;

} // namespace comum
