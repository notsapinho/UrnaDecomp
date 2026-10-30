// Pending members of the classes in mock/app/simulador/wasm/cwasmscreen.cpp. The body here is NOT the target's, it
// traps; the vtable, emitted with the class's key function in cwasmscreen.cpp, needs every slot. What it waits for:
// - CWasmScreen::Refresh(const SRect&), slot 28 (fn 9018): it keeps std::string's append a call, which -O3 gives and the
//   tree's -O2 does not (a lone link of a written 9018: 1288 rows differ at -O2, 70 at -O3).
// Not here, and no trap: CWasmScreen's slots 0 and 1, api::IScreen's destructor (fn 5071) and the deleting one around
// it (fn 8963). Both call fn 5069 (no parameters, walks a global list, unnamed); iscreen.h's `= default` does not, so
// the slots hold our defaulted bodies, not the target's, and their stubs went when this vtable came into the link.
// They wait for 5069: IScreen's destructor, inline in iscreen.h and calling it, would give both.
// Move each member into cwasmscreen.cpp when it is reconstructed, and delete this file with the last one.

#include "uenux2/mock/app/simulador/wasm/cwasmscreen.h"

namespace simulador {

void CWasmScreen::Refresh(const api::SRect&)
{
    __builtin_trap();
}

} // namespace simulador
