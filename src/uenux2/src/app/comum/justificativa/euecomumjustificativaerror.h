#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// comum::EUeComumJustificativaError, SErrorLimits{8800, 8850}: the typeinfo of CBaseError<comum::EUeComumJustificativaError,
// ...> gives the enum's name, namespace and limits. The values are the codes the two throws of
// app/comum/justificativa/dao/cjustificadordao.cpp pass; the target has 8800, 8801 and 8802 too, in members not written
// here (fns 10590, 11475). Each enumerator's name is chosen from its message: no evidence names one. The path, in the
// directory of the classes that throw it, is chosen too.
enum EUeComumJustificativaError {
    EUE_COMUM_JUSTIFICATIVA_DAO_EXCLUSAO_NAO_ESPERADA = 8804,
    EUE_COMUM_JUSTIFICATIVA_DAO_ATUALIZACAO_NAO_ESPERADA = 8805,
};

using CUeComumJustificativaError =
    ecourna::api::exception::CBaseError<EUeComumJustificativaError, ecourna::api::exception::SErrorLimits{8800, 8850}>;

} // namespace comum
