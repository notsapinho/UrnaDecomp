// Reconstruction notes, not TSE's text: this file holds comum::CParteEleitores::Imprime (fn 11206), the key function.
// The constructor, which has no target function (fn 11908 holds it inlined), is defined in
// cgeradorrellistaeleitores.cpp, the file of its one caller, MontaEleitores (src/units/317-uenux2-relatorios-aptos.mk
// says why). No record names the file or gives any of its lines.
#include "app/comum/relatorios/cparteeleitores.h"

#include "app/comum/dados/celeitores.h"

namespace comum {

void CParteEleitores::Imprime() const
{
    CEleitores& eleitores = CEleitores::GetInst();
    for (eleitores.Reset(); !eleitores.IsFim(); eleitores.Next()) {
        m_eleitor->Imprime();
    }
}

} // namespace comum
