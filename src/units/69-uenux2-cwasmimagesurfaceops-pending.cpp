// Pending members of the classes in mock/app/simulador/wasm/cwasmscreen.cpp. The bodies here are NOT the target's, they
// trap; the vtables, emitted with each class's key function in cwasmscreen.cpp, need every slot. What each waits for:
// - CWasmImageSurfaceOps::ImageSize(const std::vector<uint8_t>&), slot 12 (fn 3493, 487 B, the size of GIF, PNG, JPEG
//   bytes): its source form. Its one stack-pointer read comes after its empty test, so the parser looks like a function
//   binaryen inlined (docs/reference/facts/reading.md R10); simulador::CWasmResource's slot 4 (fn 8605) holds it too.
// - CWasmScreen::FillPath and DrawPath, slots 17 and 18 (fns 9146, 9125): fn 5113, which scales the path for both (not
//   written), then std::vector<double>'s __insert_with_size (fn 2662) for js_path.
// - CWasmScreen::DrawImage(const SPoint&, const IImage&, EAnchorPoint) and DrawImage(..., const SPoint&, EAnchorPoint),
//   slots 22 and 24 (fns 9079, 9058): both call slot 12 above, 3493, directly.
// - CWasmScreen::Refresh() and Refresh(const SRect&), slots 27 and 28 (fns 9022, 9018): fn 3533, `js_emit_event(name,
//   detail.c_str())` (22 B, table slot 59), a call where clang would inline so small a function of their TU, so read
//   as another file's, which nothing names. 9018 also keeps std::string's append a call, which -O3 gives and the
//   tree's -O2 does not (a lone link of a written 9018: 1288 rows differ at -O2, 70 at -O3).
// Not here, and no trap: CWasmScreen's slots 0 and 1, api::IScreen's destructor (fn 5071) and the deleting one around
// it (fn 8963). Both call fn 5069 (no parameters, walks a global list, unnamed); iscreen.h's `= default` does not, so
// the slots hold our defaulted bodies, not the target's, and their stubs went when this vtable came into the link.
// They wait for 5069: IScreen's destructor, inline in iscreen.h and calling it, would give both.
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
