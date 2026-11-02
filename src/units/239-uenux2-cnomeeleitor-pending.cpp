// Pending members of vota::CNomeEleitor (src/units/239-uenux2-cnomeeleitor.mk), each a slot of the vtable
// cnomeeleitor.cpp emits with the out-of-line destructor, one trap each so that the class links. These bodies are NOT
// the target's. Move each into cnomeeleitor.cpp when it is reconstructed, and delete this file with the last:
// - vota::CNomeEleitor::StartState (fn 10501, slot 2): fns 5400 and 3616, which no line of splat/symbol_addrs.txt names.
// - vota::CNomeEleitor::ProcessInput (fn 10500, slot 7, records cnomeeleitor.cpp:145 and :156, whose lines stay blank):
//   3978 B, not read further.
#include "app/vota/operador/confirmaidentidade/cnomeeleitor.h"

namespace vota {

void CNomeEleitor::StartState()
{
    __builtin_trap();
}

void CNomeEleitor::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
