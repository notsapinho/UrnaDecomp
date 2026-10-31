#pragma once

// comum::EUeComumNomeArquivoError, SErrorLimits{8950, 9000}: the typeinfo of CBaseError<comum::EUeComumNomeArquivoError, ...>
// (1558752, which every thrower passes to __cxa_throw) gives the enum's name, namespace and limits; target fn 2827 passes
// its vptr 1558772 to fn 710. The values are the codes the four throwers pass to fn 2827: 8950 (fn 2828), 8951 (fn 1161),
// 8952 (fn 3773) and 8953 (fn 3744). No evidence names an enumerator, so each name is chosen from its message; the path
// is chosen too, beside cnomearquivo.cpp, the file whose records throw it.

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

enum EUeComumNomeArquivoError {
    EUE_NOMEARQUIVO_FASE_INVALIDA = 8950,
    EUE_NOMEARQUIVO_NUMERO_EXCEDE_CASAS = 8951,
    EUE_NOMEARQUIVO_UF_INVALIDA = 8952,
    EUE_NOMEARQUIVO_ABRANGENCIA_INVALIDA = 8953,
};

using CUeComumNomeArquivoError =
    ecourna::api::exception::CBaseError<EUeComumNomeArquivoError, ecourna::api::exception::SErrorLimits{8950, 9000}>;

} // namespace comum
