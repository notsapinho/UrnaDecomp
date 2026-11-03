// Pending members of fragment 192's classes (src/units/192-uenux2-app-vota-estados-sincronismo.mk), each a slot of a
// vtable the unit's sources emit, one trap each so that the classes link. The object compiles with the unit's flags.
// What each waits for (fns 816 and 1686 match now, unit 135's, so StartState waits only to be written):
// - vota::CPedeDigital::StartState 10468 (slot 2), 851 B: calls fn 816. Records cpededigital.cpp:115, 120, 125.
// - vota::CPedeDigital::ProcessTick 10465 (slot 8), 4463 B: it calls fns 395 and 1681 (matched: unit 31,
//   src/app/roots_vector.cpp), 816 and 1686 (matched: unit 135), 1393, 3615 and 3719 (matched: units 110, 291, 91)
//   and fns 781, 1823, 1903, 2223, 2224, 2742, 5397 and 6269, which have no name. Records cpededigital.cpp:162 to 164.
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

namespace vota {

void CPedeDigital::StartState()
{
    __builtin_trap();
}

void CPedeDigital::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
