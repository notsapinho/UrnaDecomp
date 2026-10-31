// api::CClockFieldMT. No record names the file: the path is chosen, beside cledfieldmt.cpp (see
// src/units/78-uenux2-cwasmscreenmt.mk). Draw is the class's key function, so this object emits the vtable with the
// implicit destructors.

#include "api/gui/cclockfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

CClockFieldMT::CClockFieldMT(const SPoint& posicao)
    : m_posicao(posicao)
{
}

void CClockFieldMT::Draw(IScreenMT& screen) const
{
    screen.ShowClock(m_posicao);
}

} // namespace api
