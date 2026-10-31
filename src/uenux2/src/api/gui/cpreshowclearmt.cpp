// api::CPreShowClearMT. No record names the file: the path is chosen, the class's name in lower case beside the MT fields
// that lie next to it in the target (src/units/78-uenux2-cwasmscreenmt.mk). PreShow is the key function.

#include "api/gui/cpreshowclearmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CPreShowClearMT::PreShow(IScreenMT& screen)
{
    screen.Clear();
    screen.Slot13();
}

} // namespace api
