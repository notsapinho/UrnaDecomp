// Reconstruction: setters and tests of comum::CCabecalhoQRCodeBuilder under chosen names: DefineCodigoCarga,
// DefineHistoricoCarga, DefineIdUrna, DefineSecao and DefineZona (target fns 5623, 5622, 5621, 5620, 5618), IsOrigemSA and
// IsOrigemRED (5617, 5616). The record at line 284, the lambda of preBuild() (fn 2791), is not reconstructed and its line
// stays blank. That the members sit above it is a choice; their order is the target's, the higher target index first in
// the object.
#include "app/comum/relatorios/ccabecalhoqrcodebuilder.h"

#include <format>
#include <string_view>

namespace comum {

using namespace std::string_view_literals;

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

void CCabecalhoQRCodeBuilder::DefineIdUrna(uedword idUrna)
{
    m_idUrna = std::format("IDUE:{} ", idUrna);
}

void CCabecalhoQRCodeBuilder::DefineSecao(ueword secao)
{
    m_secao = std::format("SECA:{} ", secao);
}

void CCabecalhoQRCodeBuilder::DefineZona(ueword zona)
{
    m_zona = std::format("ZONA:{} ", zona);
}

bool CCabecalhoQRCodeBuilder::IsOrigemSA() const
{
    return m_origem == std::format("ORIG:{} ", "SA"sv);
}

bool CCabecalhoQRCodeBuilder::IsOrigemRED() const
{
    return m_origem == std::format("ORIG:{} ", "RED"sv);
}

// (original lines 54-280: content not recovered)
#line 281
// <stubs>
// f2791 · 562 B · unmatched · name unknown
// void f2791(i32, i32) { ... }
// </stubs>






} // namespace comum
