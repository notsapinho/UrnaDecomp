// Pending members: the api::CTextFieldUpdate members src/uenux2/src/api/gui/ctextfieldupdate.cpp does not hold yet. The
// class's vtable (emitted with the destructor, its key function, in that TU) needs them defined; their bodies are NOT the
// target's, they trap. Target functions:
//   Draw 10916   calls IScreen slots at +24 and +76, api/gui/iscreen.h's FillRect and DrawText from a point
//   Rect 10913   record ctextfieldupdate.cpp:73:21; calls fn 3889, which has no name yet
// The constructor (3658, record ctextfieldupdate.cpp:38:15) is no vtable slot and is not here: it waits for
// api::ITimerScheduler::GetInst (fn 1259) and keeps its stub in ctextfieldupdate.cpp.
// Move each into ctextfieldupdate.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfieldupdate.h"

namespace api {

void CTextFieldUpdate::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CTextFieldUpdate::Rect() const
{
    __builtin_trap();
}

} // namespace api
