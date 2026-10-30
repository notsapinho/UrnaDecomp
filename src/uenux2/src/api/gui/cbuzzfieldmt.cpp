// api::CBuzzFieldMT. No record names the file: the path is chosen, beside cledfieldmt.cpp (see
// src/units/78-uenux2-cwasmscreenmt.mk). Draw is the class's key function, so this object emits the vtable with the
// implicit destructors.

#include "api/gui/cbuzzfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CBuzzFieldMT::Draw(IScreenMT& screen) const
{
    screen.Buzz(m_primeiro, m_segundo);
}

} // namespace api

// <stubs>
// f941 · 385 B · unmatched · placement: link order · name unknown
// void f941(i32, i32, i32) { ... }
// </stubs>
