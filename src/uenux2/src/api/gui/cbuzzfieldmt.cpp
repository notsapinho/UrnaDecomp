// api::CBuzzFieldMT. No record names the file: the path is chosen, beside cledfieldmt.cpp (see
// src/units/78-uenux2-cwasmscreenmt.mk). Draw is the class's key function, so this object emits the vtable with the
// implicit destructors.

#include "api/gui/cbuzzfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

CBuzzFieldMT::CBuzzFieldMT(int primeiro, int segundo)
    : m_primeiro(primeiro)
    , m_segundo(segundo)
{
}

void CBuzzFieldMT::Draw(IScreenMT& screen) const
{
    screen.Buzz(m_primeiro, m_segundo);
}

} // namespace api
