// Pending members of fragment 192's classes (src/units/192-uenux2-app-vota-estados-sincronismo.mk), each a slot of a
// vtable the unit's sources emit, one trap each so that the classes link. The object compiles with the unit's flags.
// What each waits for:
// - vota::CPedeDigital::StartState 10468 (slot 2), 851 B: fn 816 has no name. Records cpededigital.cpp:115, 120, 125.
// - vota::CPedeDigital::FinishState 10467 (slot 5), 114 B: fn 816 has no name (its other callee,
//   api::CApplicationContextStack::Pop, fn 5553, matches: unit 193). Records cpededigital.cpp:131, 132.
// - vota::CPedeDigital::ProcessTick 10465 (slot 8), 4463 B: it calls fns 395 and 1681 (matched: unit 31,
//   src/app/roots_vector.cpp) and fns 781, 816, 1393, 1686, 1823, 1903, 2223, 2224, 2742, 3615, 3719, 5397 and 6269,
//   which have no name. Records cpededigital.cpp:162 to 164.
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

namespace vota {

void CPedeDigital::StartState()
{
    __builtin_trap();
}

void CPedeDigital::FinishState()
{
    __builtin_trap();
}

void CPedeDigital::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
