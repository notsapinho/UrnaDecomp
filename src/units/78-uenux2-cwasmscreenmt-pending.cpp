// Pending member: what the vtable of src/uenux2/mock/app/simulador/wasm/cwasmscreenmt.cpp's class needs and no source
// holds yet. Its body is NOT the target's, it traps.
//   simulador::CWasmScreenMT::ShowClock(const api::SPoint&), target fn 8757 (slot 12, 250 B). The RTTI name of its local
//     class gives the name and the parameter. It calls fn 479 (a date and time now, 12 bytes on the stack) and fn 779
//     (a member that formats the time of day at that value's +8, with the std::string "hh:mm"), builds a local class
//     WasmText : api::IText on the stack (alignment 0, the formatted string moved to +8; vtable @1530040, slots 8748, 8680,
//     1139, 1661) and calls ShowText. Its callees match: fn 779 (api::CTime::Format, unit 24) and 479 (unit 125).
//     Slots 0 and 1 of WasmText are thunks into binaryen's 1727 and 1969, so they need that merge.
#include "uenux2/mock/app/simulador/wasm/cwasmscreenmt.h"

namespace simulador {

void CWasmScreenMT::ShowClock(const api::SPoint& posicao)
{
    __builtin_trap();
}

} // namespace simulador
