#pragma once

// comum::EUeComumRelatoriosError, SErrorLimits{9050, 9150}: the typeinfo of CBaseError<comum::EUeComumRelatoriosError, ...>
// (@1543944) gives the enum's name, namespace and limits. Target fn 580, the constructor's thunk into binaryen's body 710,
// is the one body of the split that loads its vptr (1543964) as a constant. The values are every code the target passes
// to fn 580: each of its 14 direct callers (ledger/callgraph.tsv) passes a constant. No evidence names an enumerator, so
// each name is chosen and only says its value; the path is chosen too, beside the relatorios sources that throw it.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumRelatoriosError {
    EUE_COMUM_RELATORIOS_9050 = 9050,
    EUE_COMUM_RELATORIOS_9051 = 9051,
    EUE_COMUM_RELATORIOS_9052 = 9052,
    EUE_COMUM_RELATORIOS_9053 = 9053,
    EUE_COMUM_RELATORIOS_9054 = 9054,
    EUE_COMUM_RELATORIOS_9055 = 9055,
    EUE_COMUM_RELATORIOS_9056 = 9056,
    EUE_COMUM_RELATORIOS_9057 = 9057,
    EUE_COMUM_RELATORIOS_9058 = 9058,
    EUE_COMUM_RELATORIOS_9059 = 9059,
    EUE_COMUM_RELATORIOS_9060 = 9060,
    EUE_COMUM_RELATORIOS_9061 = 9061,
    EUE_COMUM_RELATORIOS_9062 = 9062,
    EUE_COMUM_RELATORIOS_9063 = 9063,
    EUE_COMUM_RELATORIOS_9064 = 9064,
    EUE_COMUM_RELATORIOS_9065 = 9065,
    EUE_COMUM_RELATORIOS_9066 = 9066,
    EUE_COMUM_RELATORIOS_9067 = 9067,
    EUE_COMUM_RELATORIOS_9068 = 9068,
    EUE_COMUM_RELATORIOS_9081 = 9081,
    EUE_COMUM_RELATORIOS_9083 = 9083,
    EUE_COMUM_RELATORIOS_9084 = 9084,
    EUE_COMUM_RELATORIOS_9085 = 9085,
    EUE_COMUM_RELATORIOS_9086 = 9086,
    EUE_COMUM_RELATORIOS_9087 = 9087,
    EUE_COMUM_RELATORIOS_9088 = 9088,
    EUE_COMUM_RELATORIOS_9089 = 9089,
};

using CUeComumRelatoriosError =
    ecourna::api::exception::CBaseError<EUeComumRelatoriosError, ecourna::api::exception::SErrorLimits{9050, 9150}>;

} // namespace comum
