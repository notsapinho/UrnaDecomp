#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// The error codes of app/comum/validamidia. The enum's name, its namespace and its limits are the target's: the typeinfo
// of CBaseError<comum::EUeComumValidaMidiaError, SErrorLimits{9200, 9250}> @1576976, whose vtable @1576988 target fn
// 11172 stores. This header's path is chosen, beside the one file that throws it. The value is the code 11172 passes, and
// its name is chosen from the message: no evidence names an enumerator.
enum EUeComumValidaMidiaError {
    // CFabricaConteudoMidiaStart::ConteudoIncializacao (inlined into fn 11172), "Não há mídia de resultado de
    // inialização para a aplicação '{}'."
    EUE_COMUM_VALIDA_MIDIA_APLICACAO_SEM_CONTEUDO = 9200,
};

using CUeComumValidaMidiaError =
    ecourna::api::exception::CBaseError<EUeComumValidaMidiaError, ecourna::api::exception::SErrorLimits{9200, 9250}>;

} // namespace comum
