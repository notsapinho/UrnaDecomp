#include "cwasminputkbd.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp)
extern "C" {
int wasm_input_get_key();
int wasm_input_has_key();
void wasm_input_clear();
}

namespace simulador {

char CWasmInputKbd::ReadKey()
{
    return static_cast<char>(wasm_input_get_key());
}

bool CWasmInputKbd::HasKey()
{
    return wasm_input_has_key() != 0;
}

void CWasmInputKbd::Clear()
{
    wasm_input_clear();
}

void CWasmInputKbd::Slot5() {}

void CWasmInputKbd::Slot6() {}

void CWasmInputKbd::Slot7() {}

} // namespace simulador
