// Pending members of the classes in mock/app/simulador/wasm/cwasmscreen.cpp. The bodies here are NOT the target's, they
// trap. The vtables, emitted with each class's key function in cwasmscreen.cpp, need every slot defined. What each waits
// for (iscreen.h has the slots, iimagesurfaceops.h the surface ops):
// - CWasmImageSurfaceOps::ImageSize(const std::vector<uint8_t>&), slot 12 (target fn 3493, 487 B), which reads the width
//   and height of GIF, PNG and JPEG bytes: its source form, not a callee. 3493 is a leaf, but its one stack-pointer read
//   comes after its empty test, where clang's prologue would not put it, so the parser looks like a function of its own
//   that binaryen inlined (docs/reference/facts/reading.md R10), and simulador::CWasmResource's slot 4 (fn 8605) holds
//   the same parser.
// - CWasmScreen::FillPath and DrawPath, slots 17 and 18 (fns 9146, 9125): each scales the path through fn 5113 (a
//   function of their own TU with these two callers, not written) and copies its doubles with
//   std::vector<double>'s __insert_with_size (fn 2662) for js_path.
// - CWasmScreen::DrawImage(const SPoint&, const IImage&, EAnchorPoint) and DrawImage(..., const SPoint&, EAnchorPoint),
//   slots 22 and 24 (fns 9079, 9058): both call slot 12 above, 3493, directly.
// - CWasmScreen::Refresh() and Refresh(const SRect&), slots 27 and 28 (fns 9022, 9018): both emit their event through
//   fn 3533, `js_emit_event(name, detail.c_str())` (22 B, table slot 59). Both call it where clang would have inlined a
//   function this small defined in their TU, so it is read as defined in another file, which nothing names. 9018 also
//   keeps std::string's append out of line, which -O3 gives and the tree's -O2 does not (a lone link of a written 9018:
//   1288 rows differ at -O2, 70 at -O3).
// Move each member into cwasmscreen.cpp when it is reconstructed, and delete this file with the last one.
#include "uenux2/mock/app/simulador/wasm/cwasmscreen.h"

namespace simulador {

api::SPoint CWasmImageSurfaceOps::ImageSize(const std::vector<uint8_t>&) const
{
    __builtin_trap();
}

void CWasmScreen::FillPath(const std::vector<api::SPathCommand>&, api::TColor)
{
    __builtin_trap();
}

void CWasmScreen::DrawPath(const std::vector<api::SPathCommand>&, api::TColor, int)
{
    __builtin_trap();
}

void CWasmScreen::DrawImage(const api::SPoint&, const api::IImage&, api::EAnchorPoint)
{
    __builtin_trap();
}

void CWasmScreen::DrawImage(const api::SPoint&, const api::IImage&, const api::SPoint&, api::EAnchorPoint)
{
    __builtin_trap();
}

void CWasmScreen::Refresh()
{
    __builtin_trap();
}

void CWasmScreen::Refresh(const api::SRect&)
{
    __builtin_trap();
}

} // namespace simulador
