// Pending members of the classes in mock/app/simulador/wasm/cwasmscreen.cpp. The body here is NOT the target's, it
// traps; the vtable, emitted with the class's key function in cwasmscreen.cpp, needs every slot. What it waits for:
// - CWasmScreen::Refresh(const SRect&), slot 28 (fn 9018): it keeps std::string's append a call, which -O3 gives and the
//   tree's -O2 does not. A written 9018 (the rectangle's scaled corners, width and height joined by std::string's
//   operator+ into a JSON text for EmitEvent, as Refresh() does) scores 1301 over 1743 rows in the whole link at -O2,
//   where clang inlines all 12 appends (the object calls __grow_by_and_replace instead), and 49 over 725 with
//   cwasmscreen.cpp.o compiled at -O3, which keeps the 12 append calls. What is left there is the width and height:
//   the target narrows std::abs(x1 - x2) + 1 to 16 bits with one extend16_s, and every form tried in a probe, at both
//   levels, gives a shift pair (a TPosition local, a static_cast, ++ on a TPosition, a helper returning one).
// Move each member into cwasmscreen.cpp when it is reconstructed, and delete this file with the last one.

#include "uenux2/mock/app/simulador/wasm/cwasmscreen.h"

namespace simulador {

void CWasmScreen::Refresh(const api::SRect&)
{
    __builtin_trap();
}

} // namespace simulador
