// Pending members of simulador::CWasmInit (mock/app/simulador/wasm/cwasminit.cpp). The body here is NOT the target's,
// it traps; the vtable, emitted with the class's key function in cwasminit.cpp, needs every slot. What it waits for:
// - EnviarMensagem, slot 5 (fn 9405): a switch over the message that logs each one with a text through fn 1524 and
//   answers with a one-element std::vector<int>. 1524 (its stub is in src/uenux2/unplaced.cpp) formats
//   "CWasmInit::{} {}" and hands the line to fn 5152, a 3711-byte writer over a std::ostringstream that no unit has
//   yet, which simulador::CWasmLogd's slot 2 (fn 8327) calls as well.
// Move the member into cwasminit.cpp when it is reconstructed, and delete this file with it.

#include "uenux2/mock/app/simulador/wasm/cwasminit.h"

namespace simulador {

std::vector<int> CWasmInit::EnviarMensagem(ueint32)
{
    __builtin_trap();
}

} // namespace simulador
