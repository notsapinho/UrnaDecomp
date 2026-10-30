// Pending members: the api::CTextFieldUpdate members src/uenux2/src/api/gui/ctextfieldupdate.cpp does not hold yet. The
// class's vtable (emitted with the destructor, its key function, in that TU) needs them defined; their bodies are NOT the
// target's, they trap. Target functions:
//   Draw 10916   calls IScreen slots at +24 and +76, which api/gui/iscreen.h does not declare yet
//   Show 10915   calls slot 2 of the timer at +72, and Hide 10914 its slot 3, Start and Stop in api/util/itimer.h,
//                which the class header does not include: it only forward-declares api::ITimer
//   Rect 10913   record ctextfieldupdate.cpp:73:21; calls fn 3889, which has no name yet
//   Move 2241    binaryen's one body for CImageField, CDSImageField, CImageFieldUpdate, CTextFieldBlinking, CTextField and
//                this class
// The constructor (3658, record ctextfieldupdate.cpp:38:15) is no vtable slot and is not here: it waits for
// api::ITimerScheduler::GetInst (fn 1259) and keeps its stub in ctextfieldupdate.cpp.
// Move each into ctextfieldupdate.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfieldupdate.h"

namespace api {

void CTextFieldUpdate::Draw(IScreen&) const
{
    __builtin_trap();
}

void CTextFieldUpdate::Show()
{
    __builtin_trap();
}

void CTextFieldUpdate::Hide()
{
    __builtin_trap();
}

SRect CTextFieldUpdate::Rect() const
{
    __builtin_trap();
}

void CTextFieldUpdate::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
