// api::CClockFieldMT. No record names the file: the path is chosen, beside cledfieldmt.cpp (see
// src/units/78-uenux2-cwasmscreenmt.mk). Draw is the class's key function, so this object emits the vtable with the
// implicit destructors.

#include "api/gui/cclockfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CClockFieldMT::Draw(IScreenMT& screen) const
{
    screen.ShowClock(m_posicao);
}

} // namespace api

// <stubs>
// f728 · 381 B · unmatched · placement: link order · name unknown
// void f728(i32, i32) { ... }
// </stubs>
