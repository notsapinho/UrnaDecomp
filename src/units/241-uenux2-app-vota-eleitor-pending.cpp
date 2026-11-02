// Pending members of fragment 241's classes (src/units/241-uenux2-app-vota-eleitor.mk), each its class's key function,
// so this object emits both vtables; trapped so that the classes link. Their bodies are NOT the target's. What each
// waits for:
// - vota::CFimVotoEleitor::StartState 7198 (slot 2), 207 B, record cfimvotoeleitor.cpp:42 (that line stays blank
//   there): it passes a 3-character std::string (the bytes at 150256) to fn 1204, which has no name and is not written;
//   its other callees (CTelasVota::GetInst 407, instance<IBeep> 925, CEstadoAudio::GetInst 509,
//   CThreadOperador::GetInst 270, the queue's Insert 501, CAguardaMensagem::GetInst 1337) are matched or named (pnpm
//   wasm fn of 7198; splat/matched.txt, splat/symbol_addrs.txt).
// - vota::impl::CSincronismoVotoEleitor::Sincroniza 7174 (slot 2), 3288 B: it holds the records of
//   csincronizavota.cpp's vota::(anonymous namespace)::SincronizaRDVInternoSeguro and SincronizaRDVExternoSeguro (lines
//   290 and 303), so it calls into that file, and of the 48 functions it calls (imports aside) fns 1551, 1692, 1701,
//   2369, 2543, 2826, 3789 and 3790 have no name and no match. Its stub, which sat at csincronizavota.cpp:287, goes
//   with this trap.
#include "app/vota/eleitor/cfimvotoeleitor.h"
#include "app/vota/eleitor/csincronismovotoeleitor.h"

namespace vota {

void CFimVotoEleitor::StartState()
{
    __builtin_trap();
}

namespace impl {

bool CSincronismoVotoEleitor::Sincroniza()
{
    __builtin_trap();
}

} // namespace impl

} // namespace vota
