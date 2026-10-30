// Pending member: simulador::CWasmImageSurfaceOps's ImageSize(const std::vector<uint8_t>&) (slot 12, target fn 3493,
// 487 B), which reads the width and height of GIF, PNG and JPEG bytes. Its vtable, emitted with the key function in
// mock/app/simulador/wasm/cwasmscreen.cpp, needs every slot defined. The body here is NOT the target's, it traps. What
// it waits for is its source form, not a callee. 3493 is a leaf, but its one stack-pointer read comes after its empty
// test, where clang's prologue would not put it, so the parser looks like a function of its own that binaryen inlined
// (docs/reference/facts/reading.md R10), and simulador::CWasmResource's slot 4 (fn 8605) holds the same parser. Move
// the member into that file when it is reconstructed, and delete this file with it.
#include "uenux2/mock/app/simulador/wasm/cwasmimagesurfaceops.h"

namespace simulador {

api::SPoint CWasmImageSurfaceOps::ImageSize(const std::vector<uint8_t>&) const
{
    __builtin_trap();
}

} // namespace simulador
