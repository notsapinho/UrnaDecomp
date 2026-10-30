// api::CBeepFieldMT. No record names the file: the path is chosen, beside cledfieldmt.cpp, the one recorded file of the
// MT fields (src/units/78-uenux2-cwasmscreenmt.mk says what the data order does and does not show). Draw is the class's
// key function, so this object emits the vtable with the implicit destructors.

#include "api/gui/cbeepfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CBeepFieldMT::Draw(IScreenMT& screen) const
{
    screen.Beep(m_vezes);
}

} // namespace api
