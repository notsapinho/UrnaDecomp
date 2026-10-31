#pragma once

#include <string>

#include "app/comum/eurnafase.h"

namespace comum {

// Reconstruction notes, not TSE's text. comum::CRelUtil: the records of crelutil.cpp name the class and five functions,
// four of them static members (GetIDCargaFormatado, line 69; IncluiCabecalhoEleicoesMZS, 307; DSCodigoVerificador, 412;
// GetSeparadorFase, 554). Only GetSeparadorFase (target fn 1919) is reconstructed, and only it is declared. This header's
// path is chosen, beside the .cpp.
class CRelUtil {
public:
    static std::string GetSeparadorFase(const EUrnaFase fase);
};

} // namespace comum
