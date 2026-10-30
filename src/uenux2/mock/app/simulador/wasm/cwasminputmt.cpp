#include "cwasminputmt.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp)
extern "C" {
int wasm_input_get_key();
int wasm_input_has_key();
void wasm_input_clear();
}

namespace simulador {

char CWasmInputMT::ReadKey()
{
    return static_cast<char>(wasm_input_get_key());
}

bool CWasmInputMT::HasKey()
{
    return wasm_input_has_key() != 0;
}

void CWasmInputMT::Clear()
{
    wasm_input_clear();
}

} // namespace simulador
