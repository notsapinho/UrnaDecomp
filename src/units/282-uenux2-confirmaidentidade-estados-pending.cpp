// Pending members of the classes of src/units/282-uenux2-confirmaidentidade-estados.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CDigitalReconhecida::ProcessInput (target fn 10481, slot 7, 926 B): it calls fn 3266 (217 B), which no line
//   of splat/symbol_addrs.txt names, and fn 2499 (a __tree::destroy our link pairs with another map's, differs).
#include "app/vota/operador/confirmaidentidade/cdigitalreconhecida.h"

namespace vota {

void CDigitalReconhecida::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
