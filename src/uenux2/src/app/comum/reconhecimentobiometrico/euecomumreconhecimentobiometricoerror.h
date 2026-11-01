#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// comum::EUeComumReconhecimentoBiometricoError, SErrorLimits{9000, 9050}: the typeinfo of CBaseError<...> gives the
// enum's name, namespace and limits. The values are the codes fn 2725 (CControlaArmazenamentoDeImagens' static
// functions, ccontrolaarmazenamentodeimagens.cpp, not written) throws: 9000 with "O arquivo " (@441359), a path and
// " não existe" (@173392, the tail of the literal at 173354), 9001 with "O arquivo ", a path and " está vazio" (@130331).
// Each enumerator's name is chosen from its message: no evidence names one. The path, beside the class that throws it,
// is chosen too. Only src/units/186-uenux2-chasharquivo-roots.cpp throws it in this tree.
enum EUeComumReconhecimentoBiometricoError {
    EUE_COMUM_RECONHECIMENTO_BIOMETRICO_ARQUIVO_NAO_EXISTE = 9000,
    EUE_COMUM_RECONHECIMENTO_BIOMETRICO_ARQUIVO_VAZIO = 9001,
};

using CUeComumReconhecimentoBiometricoError =
    ecourna::api::exception::CBaseError<EUeComumReconhecimentoBiometricoError,
                                        ecourna::api::exception::SErrorLimits{9000, 9050}>;

} // namespace comum
