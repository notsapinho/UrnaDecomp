// Pending members: the api::CTextBox members src/uenux2/src/api/gui/ctextbox.cpp does not hold yet. Draw is the class's
// key function, so this object emits the vtable, with the implicit destructors (target fns 10955, 10954) and the inline
// GetTypeName (10953), which are the compiler's code for the class definition and match from here; they move with the
// vtable when Draw lands. The bodies below are NOT the target's, they trap. Target functions:
//   10958 Draw(IScreen&) const: record ctextbox.cpp:69:19, "Status indefinido"; calls IScreen's slots 5, 6, 9, 19 and
//         29 (vtable offsets 20, 24, 36, 76, 116), iscreen.h's Clear, FillRect, DrawRect, DrawText and SetColors
//   10956 Rect() const: record ctextbox.cpp:110:9; calls CPolySingleton<IScreen>'s instance (fn 512), which has no name
//         yet, to reach IScreen::GetFontMetrics
// Move each into ctextbox.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextbox.h"

namespace api {

void CTextBox::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CTextBox::Rect() const
{
    __builtin_trap();
}

} // namespace api
