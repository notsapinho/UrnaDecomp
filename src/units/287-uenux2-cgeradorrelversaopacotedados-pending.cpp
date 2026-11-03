// Pending members of comum::CGeradorRelVersaoPacoteDados (src/units/287-uenux2-cgeradorrelversaopacotedados.mk). The
// class's vtable needs every slot defined; these bodies are NOT the target's, they trap. Move each into
// src/uenux2/src/app/comum/relatorios/cgeradorrelversaopacotedados.cpp when it is reconstructed, and delete this file
// with the last.
//
// - ImprimeTituloJE (target fn 11223, slot 3, 2163 B): it calls comum::CRelUtil::IncluiCabecalhoEleicoesMZS (fn 1543)
//   and fns 1541, 1921, 1922, 2785, 2787 and 2788, none named here, and 2273 (CAppInfo::LeGeralInterno, unit 296's), and builds the std::function of its lambda
//   (vtable @1576316, slots 11221, 11219, 11218 and 11217, which come with it).
#include "app/comum/relatorios/cgeradorrelversaopacotedados.h"

namespace comum {

void CGeradorRelVersaoPacoteDados::ImprimeTituloJE()
{
    __builtin_trap();
}

} // namespace comum
