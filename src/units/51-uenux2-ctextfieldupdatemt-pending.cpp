// Pending members: the api::CTextFieldUpdateMT member src/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.cpp
// does not hold yet. The class's vtable (emitted with the destructor, its key function, in that TU) needs it defined;
// its body is NOT the target's, it traps. Target function:
//   Draw 10548   calls slot 2 of the SharedIText at +28 (IText::GetText) and slot 3 of the screen twice (the erase
//                with a temporary text of spaces, vptr 1532648, when the new text is shorter, then the text itself),
//                which api/gui has no IScreenMT header to declare yet; it keeps the text it drew at +36
// The constructor (inlined into fn 652, no target function of its own) is no vtable slot and is not here: it waits for
// api::ITimerScheduler::GetInst (fn 1259).
// Move it into ctextfieldupdatemt.cpp when it is reconstructed; delete this file and its rule with it.
#include "app/vota/operador/comum/ctextfieldupdatemt.h"

namespace api {

void CTextFieldUpdateMT::Draw(IScreenMT&) const
{
    __builtin_trap();
}

} // namespace api
