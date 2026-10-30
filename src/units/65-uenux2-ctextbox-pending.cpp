// Pending member: the api::CTextBox member src/uenux2/src/api/gui/ctextbox.cpp does not hold yet. The class's vtable
// (emitted with Draw, its key function, in that TU) needs it defined; its body is NOT the target's, it traps. Target
// function:
//   10956 Rect() const: record ctextbox.cpp:110:9; calls CPolySingleton<IScreen>'s instance (fn 512), which has no name
//         yet, to reach IScreen::GetFontMetrics
// Move it into ctextbox.cpp when it is reconstructed and delete this file.
#include "api/gui/ctextbox.h"

namespace api {

SRect CTextBox::Rect() const
{
    __builtin_trap();
}

} // namespace api
