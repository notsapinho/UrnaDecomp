// Pending members: the vota::CExibeAlertaDesligamento overriders
// src/uenux2/src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp does not hold yet. The class's vtable is
// emitted there with the destructor, its key function, and needs them defined; their bodies are NOT the target's, they
// trap. Target functions, both reached only through the vtable:
// - StartState 12018 (slot 2, record cexibealertadesligamento.cpp:45:5): sets the next state to this one, calls slot 2
//   of the +24 form, copies a 12-byte static api::CDateTime (@1833312) into +12 and calls slot 1 (2000, 100) of the
//   api::IBeep that api::CPolySingleton<api::IBeep>::instance (fn 925) returns;
// - ProcessTick 12017 (slot 8, records cexibealertadesligamento.cpp:53:13 and 54:24): on its own tick, compares +12 with
//   the current time (fns 479 and 759, api::CDateTime members with no name yet); past it, logs "Tempo limite de espera
//   usando bateria interna atingido" (vota::CLogVota::GetInst, fn 184, and api::CLoga::loga, fn 433) and calls
//   comum::IInterfaceInit::DesligarUrna (fn 5894) on CPolySingleton<comum::IInterfaceInit>'s instance (fn 611); else
//   goes to the +36 state when slot 15 of CPolySingleton<api::IPower>'s instance (fn 862) says so. Of those
//   callees only the three instances are reconstructed.
// Move each into cexibealertadesligamento.cpp, at its records' lines, when it is reconstructed; delete this file with
// the last one.
#include "app/vota/eleitor/iniciovotacao/cexibealertadesligamento.h"

namespace vota {

void CExibeAlertaDesligamento::StartState()
{
    __builtin_trap();
}

void CExibeAlertaDesligamento::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
