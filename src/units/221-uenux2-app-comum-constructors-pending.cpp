// Pending members of vota::CRegistraDigitalOperador (src/units/221-uenux2-app-comum-constructors.mk), each reached only
// through its vtable, which cregistradigitaloperador.cpp emits with the destructor and which needs every slot defined.
// These bodies are NOT the target's, they trap. Move each into cregistradigitaloperador.cpp when it is reconstructed,
// and delete this file with the last.
//
// - vota::CRegistraDigitalOperador::ProcessTick (target fn 10451, slot 8, 6996 B, records :143 to :145): it calls
//   BiometriaMesarioPresenteNosEleitores (fn 3614, three call sites, records :328 and :371, not written), fn 2972
//   (libm's log2, matched with fragment 335's 5702), fns 5372 and 5376, none matched or named (splat/matched.txt,
//   splat/symbol_addrs.txt), 5371 (unit 214's, matched), 2223 and 2742 (matched with unit 282's 10465; 10316, unit
//   135's, calls both too, and 2725 2742), 2805 (matched,
//   unit 310's, from the converter of the voters' file),
//   1149 and 5374 (unit 214's), 3615 (unit 291's) and 3258 (unit 119's CLogVota::LogaMesarioHabilitouEleitor), matched, and 5399 (unit 282's CInformaEleitorPodeVotar::GetInst,
//   matched), and it holds the GetInst and constructor of vota::CTentativaCapturaDigitalEsgotada and
//   vota::CDigitalNaoCapturada inlined (the one store of each vptr, 1592288 and 1592360).
#include "app/vota/operador/confirmaidentidade/cregistradigitaloperador.h"

namespace vota {

void CRegistraDigitalOperador::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
