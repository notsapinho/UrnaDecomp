// Pending members of vota::CEscolheOpcao (src/units/121-uenux2-datasources.mk), each a slot of the vtable
// cescolheopcao.cpp emits with the out-of-line destructor, one trap each so that the class links. The object compiles
// with the unit's flags. What each waits for:
// - vota::CEscolheOpcao::ProcessInput 10689 (slot 7): it calls fns 395 (unit 31) and 5430 (unit 152), matched, and
//   fns 652, 2502 and 3610, which have no name.
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

void CEscolheOpcao::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
