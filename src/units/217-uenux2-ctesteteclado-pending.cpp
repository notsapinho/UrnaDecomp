// Pending member of src/units/217-uenux2-ctesteteclado.mk: the slot vota::testeteclado::CTesteTeclado's vtable needs
// and src/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp does not hold yet. Its body is NOT
// the target's, it traps. It is reached only through the vtable. What it waits for (a callee "with no name" has no line
// in splat/matched.txt or splat/symbol_addrs.txt):
// - ProcessInput 11804 (slot 7, 1437 B, records ctesteteclado.cpp:50, :60 and :81): not written. Every callee has a
//   body of ours and matches (fn 653, api::CInteractiveFormBuilder::AddLabeledInputControl, since unit 120 wrote it);
//   940 and 3854 are this unit's.
// Its record lines in ctesteteclado.cpp stay blank, between StartState and the constructor. Move it into
// ctesteteclado.cpp when it is reconstructed, and delete this file then.
#include "app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.h"

namespace vota::testeteclado {

void CTesteTeclado::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota::testeteclado
