#include "api/gui/cclockfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CClockFieldMT::Draw(IScreenMT& screen) const
{
    screen.ShowClock(m_posicao);
}

} // namespace api
