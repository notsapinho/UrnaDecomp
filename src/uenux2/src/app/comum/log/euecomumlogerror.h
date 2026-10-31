#pragma once

// comum::EUeComumLogError, SErrorLimits{8850, 8900}: the typeinfo of CBaseError<comum::EUeComumLogError, ...> gives the
// enum's name, namespace and limits (typeinfo 1552868, target fn 2861 passes its vptr 1552936 to fn 710). The values
// are the codes fns 5879 and 5875 pass. No evidence names an enumerator, so each name is chosen and only says its value;
// the path is chosen too, beside the files whose records throw it.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumLogError {
    EUE_COMUM_LOG_8852 = 8852,
    EUE_COMUM_LOG_8853 = 8853,
    EUE_COMUM_LOG_8854 = 8854,
};

using CUeComumLogError = ecourna::api::exception::CBaseError<EUeComumLogError, ecourna::api::exception::SErrorLimits{8850, 8900}>;

} // namespace comum
