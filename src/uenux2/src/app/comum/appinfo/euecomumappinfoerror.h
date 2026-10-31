#pragma once

// comum::EUeComumAppInfoError, SErrorLimits{7600, 7650}: the typeinfo of CBaseError<comum::EUeComumAppInfoError, ...> gives
// the enum's name, namespace and limits (vptr 1558004, target fn 1710 passes it). The values are the codes fns 291, 457 and
// 1553 pass. No evidence names an enumerator, so each name is chosen from its message; the path is chosen too, beside
// cappinfo.cpp, the file the throws are in.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumAppInfoError {
    EUE_APPINFO_ESTADO_NAO_CARREGADO = 7600,
    EUE_APPINFO_ESTADO_CONST_NAO_CARREGADO = 7601,
    EUE_APPINFO_TURNO_INVALIDO = 7602,
};

using CUeComumAppInfoError =
    ecourna::api::exception::CBaseError<EUeComumAppInfoError, ecourna::api::exception::SErrorLimits{7600, 7650}>;

} // namespace comum
