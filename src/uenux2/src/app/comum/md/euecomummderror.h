#pragma once

// comum::EUeComumMdError, SErrorLimits{8900, 8950}: the name, namespace and limits are the typeinfo's at 1552724, and the
// calls of the constructor's thunk, fn 591, give the codes. No record names this header: its path is chosen, beside the
// files that throw the error. No evidence names an enumerator: each is the code, as in euecomumdadoserror.h.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumMdError {
    EUE_COMUM_MD_8900 = 8900,
    EUE_COMUM_MD_8901 = 8901,
    EUE_COMUM_MD_8902 = 8902,
    EUE_COMUM_MD_8903 = 8903,
    EUE_COMUM_MD_8904 = 8904,
    EUE_COMUM_MD_8905 = 8905,
    EUE_COMUM_MD_8914 = 8914,
    EUE_COMUM_MD_8915 = 8915,
    EUE_COMUM_MD_8916 = 8916,
    EUE_COMUM_MD_8917 = 8917,
    EUE_COMUM_MD_8918 = 8918,
    EUE_COMUM_MD_8919 = 8919,
    EUE_COMUM_MD_8920 = 8920,
    EUE_COMUM_MD_8925 = 8925,
    EUE_COMUM_MD_8926 = 8926,
    EUE_COMUM_MD_8927 = 8927,
};

using CUeComumMdError =
    ecourna::api::exception::CBaseError<EUeComumMdError, ecourna::api::exception::SErrorLimits{8900, 8950}>;

} // namespace comum
