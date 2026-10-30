#pragma once

// comum::EUeComumAsnError, SErrorLimits{7650, 7750}: the typeinfo of CBaseError<comum::EUeComumAsnError, ...> (1528108)
// gives the enum's name, namespace and limits, and the target's calls of the constructor's thunk, fn 255, give the
// codes. No record names this header: its path is chosen, beside the files that throw the error. No evidence names an
// enumerator: each name is chosen from the message its throw builds. A code no written function throws has no
// enumerator yet.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumAsnError {
    EUE_COMUM_ASN_FASE_INVALIDA_CONVERTE = 7674,
    EUE_COMUM_ASN_FASE_INVALIDA_DESCONVERTE = 7675,
    EUE_COMUM_ASN_ABRANGENCIA_INVALIDA = 7686,
    EUE_COMUM_ASN_TIPO_LOCAL_INVALIDO_CONVERTE = 7687,
    EUE_COMUM_ASN_TIPO_LOCAL_INVALIDO_DESCONVERTE = 7688,
};

using CUeComumAsnError =
    ecourna::api::exception::CBaseError<EUeComumAsnError, ecourna::api::exception::SErrorLimits{7650, 7750}>;

} // namespace comum
