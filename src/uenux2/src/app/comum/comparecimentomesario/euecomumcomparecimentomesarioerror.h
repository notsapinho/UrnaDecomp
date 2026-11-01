#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// comum::EUeComumComparecimentoMesarioError, SErrorLimits{7750, 7800}: the typeinfo of
// CBaseError<comum::EUeComumComparecimentoMesarioError, ...> (1593412) gives the enum's name, namespace and limits. The
// values are the codes the two converters of app/comum/comparecimentomesario/dao/ccomparecimentomesariodao.cpp throw
// (fns 5391 and 5390). Each enumerator's name is chosen from its message: no evidence names one. The path, in the
// directory of the classes that throw it, is chosen too.
enum EUeComumComparecimentoMesarioError {
    EUE_COMUM_COMPARECIMENTO_MESARIO_ESTADO_BIOMETRIA_INVALIDO = 7755,
    EUE_COMUM_COMPARECIMENTO_MESARIO_DEDO_HABILITACAO_INVALIDO = 7756,
};

using CUeComumComparecimentoMesarioError =
    ecourna::api::exception::CBaseError<EUeComumComparecimentoMesarioError, ecourna::api::exception::SErrorLimits{7750, 7800}>;

} // namespace comum
