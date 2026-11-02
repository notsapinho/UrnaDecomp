// Pending members of vota::CEscolheOpcao (src/units/121-uenux2-datasources.mk), each a slot of the vtable
// cescolheopcao.cpp emits with the out-of-line destructor, one trap each so that the class links. The object compiles
// with the unit's flags. What each waits for:
// - vota::CEscolheOpcao::StartState 10690 (slot 2), 240 B: fn 2946 has no name. Records cescolheopcao.cpp:150 to 152,
//   whose lines stay blank there.
// - vota::CEscolheOpcao::ProcessInput 10689 (slot 7): it calls fn 395, which no form has matched, and fns 652, 2502, 3610
//   and 5430, which have no name.
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

void CEscolheOpcao::StartState()
{
    __builtin_trap();
}

void CEscolheOpcao::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
