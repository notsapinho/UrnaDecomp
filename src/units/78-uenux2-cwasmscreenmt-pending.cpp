// Pending members: what the vtables of src/uenux2/mock/app/simulador/wasm/cwasmscreenmt.cpp's class and of api::IScreenMT
// need and no source holds yet. Their bodies are NOT the target's, they trap.
//   simulador::CWasmScreenMT::ShowClock(const api::SPoint&), target fn 8757 (slot 12, 250 B). The RTTI name of its local
//     class gives the name and the parameter. It calls fn 479 (a date and time now, 12 bytes on the stack) and fn 779
//     (a member that formats the time of day at that value's +8, with the std::string "hh:mm"), builds a local class
//     WasmText : api::IText on the stack (alignment 0, the formatted string moved to +8; vtable @1530040, slots 8748, 8680,
//     1139, 1661) and calls ShowText. It waits for fns 479 and 779, which have no body of ours: 479 calls fns 1155 (1944 B)
//     and 1000. Slots 0 and 1 of WasmText are thunks into binaryen's 1727 and 1969, so they need that merge as well.
//   api::IScreenMT::~IScreenMT(), target fn 8741 (slot 0 of its vtable, 17 B), the vptr store and a call of fn 3461. Inline
//     in the original: api/gui/iscreenmt.h says why, and it moves into the class with its body. The trap makes it the key
//     function of our link only, so this object emits IScreenMT's vtable and typeinfo, which CWasmScreenMT's typeinfo
//     names. It waits for fn 3461 (148 B, no body of ours): that function empties a stack of forms in .bss (the vector at
//     1832892, a mutex at 1832864, reading as CFormStack<IScreenMT>'s from the forms' layout in api/gui/iform.h, which is a
//     reading, not evidence), then calls fn 2631, which notifies the observers at 1529940.
//     CWasmScreenMT's D2 and D0 (fns 8745, 8744) are the implicit ones, emitted with its vtable by cwasmscreenmt.cpp; they
//     hold this body inlined in the target, so they differ from the target's, in that call only, until it lands.
#include "uenux2/mock/app/simulador/wasm/cwasmscreenmt.h"

namespace api {

IScreenMT::~IScreenMT()
{
    __builtin_trap();
}

} // namespace api

namespace simulador {

void CWasmScreenMT::ShowClock(const api::SPoint& posicao)
{
    __builtin_trap();
}

} // namespace simulador
