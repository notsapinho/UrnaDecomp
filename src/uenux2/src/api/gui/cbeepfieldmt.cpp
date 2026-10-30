#include "api/gui/cbeepfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CBeepFieldMT::Draw(IScreenMT& screen) const
{
    screen.Beep(m_vezes);
}

} // namespace api
