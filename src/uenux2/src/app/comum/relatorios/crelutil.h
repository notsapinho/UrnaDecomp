#pragma once

#include <string>

#include "app/comum/eurnafase.h"

namespace api {
class CPaperFormBuilder;
} // namespace api

namespace comum {

// Reconstruction notes, not TSE's text. comum::CRelUtil: the records of crelutil.cpp name the class and five functions,
// four of them static members (GetIDCargaFormatado, line 69; IncluiCabecalhoEleicoesMZS, 307; DSCodigoVerificador, 412;
// GetSeparadorFase, 554). Reconstructed and declared: GetIDCargaFormatado (target fn 2786), GetSeparadorFase (fn 1919) and
// IncluiAvisoModoDemonstracao (fn 5583), a static member by choice whose name is chosen: no record names it; it adds the
// demonstration mode's warning to a report and is called by IncluiCabecalhoEleicoesMZS (fn 1543) and fn 5591. This
// header's path is chosen, beside the .cpp.
class CRelUtil {
public:
    static std::string GetIDCargaFormatado(const std::string& idCarga);
    static void IncluiAvisoModoDemonstracao(api::CPaperFormBuilder& builder);
    static std::string GetSeparadorFase(const EUrnaFase fase);
};

} // namespace comum
