// Pending members of vota::CRegistraDigitalOperador (src/units/221-uenux2-app-comum-constructors.mk), each reached only
// through its vtable, which cregistradigitaloperador.cpp emits with the destructor and which needs every slot defined.
// These bodies are NOT the target's, they trap. Move each into cregistradigitaloperador.cpp when it is reconstructed,
// and delete this file with the last.
//
// - vota::CRegistraDigitalOperador::FinishState (target fn 10453, slot 5, 17 B): `f6012(p0, <record :105>, <record
//   :104>)`, a thunk into the body binaryen merged from it and comum::CPedeDigitalMesario::FinishState (fn 10315, a
//   trap of unit 135), which the target holds as fn 6012. Its source, from 6012 and the records
//   cregistradigitaloperador.cpp :104 and :105 (column 5):
//       api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
//       api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
//   It waits for 10315: written alone, either is a whole body where the target has a thunk.
// - vota::CRegistraDigitalOperador::ProcessTick (target fn 10451, slot 8, 6996 B, records :143 to :145): it calls
//   BiometriaMesarioPresenteNosEleitores (fn 3614, three call sites, records :328 and :371, not written), fns 1149,
//   2223, 2742, 2805, 2972, 3258, 3615, 5371, 5372, 5374 and 5376, none matched or named (splat/matched.txt,
//   splat/symbol_addrs.txt), and 5399 (unit 282's CInformaEleitorPodeVotar::GetInst, written and `unresolved`), and it
//   holds the GetInst and constructor of vota::CTentativaCapturaDigitalEsgotada and vota::CDigitalNaoCapturada inlined
//   (the one store of each vptr, 1592288 and 1592360).
#include "app/vota/operador/confirmaidentidade/cregistradigitaloperador.h"

namespace vota {

void CRegistraDigitalOperador::FinishState()
{
    __builtin_trap();
}

void CRegistraDigitalOperador::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
