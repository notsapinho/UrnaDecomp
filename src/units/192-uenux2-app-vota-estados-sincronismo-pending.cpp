// Pending members of fragment 192's classes (src/units/192-uenux2-app-vota-estados-sincronismo.mk), each a slot of a
// vtable the unit's sources emit, one trap each so that the classes link. The object compiles with the unit's flags.
// What each waits for:
// - vota::CSincronismoEleitor::ProcessKey 7181 (slot 6), 2072 B: fns 2741 and 5398 have no name. It holds
//   vota::impl::ISincronismoVotoEleitor::GetInst inlined (record app/vota/eleitor/csincronismovotoeleitor.cpp:67), the
//   one record of that file, which was a stub-only file holding 7181's stub alone: writing the member writes that file
//   again.
// - vota::CPedeDigital::StartState 10468 (slot 2), 851 B: fn 816 has no name. Records cpededigital.cpp:115, 120, 125.
// - vota::CPedeDigital::FinishState 10467 (slot 5), 114 B: fn 816 has no name, and it calls
//   api::CApplicationContextStack::Pop (fn 5553), which is written and does not match. Records cpededigital.cpp:131, 132.
// - vota::CPedeDigital::ProcessTick 10465 (slot 8), 4463 B: it calls fn 395, which no form has matched, and fns 781, 816,
//   1393, 1681, 1686, 1823, 1903, 2223, 2224, 2742, 3615, 3719, 5397 and 6269, which have no name. Records
//   cpededigital.cpp:162 to 164.
#include "app/vota/eleitor/csincronismoeleitor.h"
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

namespace vota {

void CSincronismoEleitor::ProcessKey(uebyte)
{
    __builtin_trap();
}

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
