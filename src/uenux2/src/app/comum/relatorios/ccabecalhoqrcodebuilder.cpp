// Reconstruction: two setters of comum::CCabecalhoQRCodeBuilder under chosen names, DefineCodigoCarga and
// DefineHistoricoCarga (target fns 5623, 5622). The record at line 284, the lambda of preBuild() (fn 2791), is not
// reconstructed and its line stays blank. That the setters sit above it is a choice; their order is the target's, the
// higher target index first in the object.
#include "app/comum/relatorios/ccabecalhoqrcodebuilder.h"

#include <format>

namespace comum {

void CCabecalhoQRCodeBuilder::DefineCodigoCarga(const std::string& codigoCarga)
{
    m_codigoCarga = std::format("IDCA:{:.24s} ", codigoCarga);
}

void CCabecalhoQRCodeBuilder::DefineHistoricoCarga(const std::vector<std::string>& cargas)
{
    m_historicoCarga = std::format("HIQT:{} ", cargas.size());
    unsigned indice = 0;
    for (const std::string& carga : cargas) {
        m_historicoCarga += std::format("HICA:{}:{:.24s} ", ++indice, carga);
    }
}

// (original lines 25-280: content not recovered)
#line 281
// <stubs>
// f2791 · 562 B · unmatched · name unknown
// void f2791(i32, i32) { ... }
// </stubs>






} // namespace comum
