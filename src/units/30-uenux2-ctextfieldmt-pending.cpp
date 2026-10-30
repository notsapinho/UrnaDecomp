// Pending members: the api::CTextFieldMT member src/uenux2/src/api/gui/ctextfieldmt.cpp does not hold yet. Draw is the
// class's only virtual member defined out of line (its key function), so the vtable is emitted here, and with it what
// the vtable names that the class declares implicitly or inherits inline: the destructors (target fns 10933, 10932)
// and IFormField<IScreenMT>::GetTypeName (11051, inline in api/gui/iformfield.h; the link keeps the copy of the first
// object that emits it, ctextfieldupdatemt.cpp.o). Those are the compiler's code for the class definition, not
// stand-ins; they move to ctextfieldmt.cpp's object with the vtable when Draw lands.
// Draw's body is NOT the target's, it traps. Target function: Draw 10934 (666 B), which draws through IScreenMT's
// vtable (slot 3, api/gui/iscreenmt.h's Slot3) and builds an api::CFixedText of spaces to erase the previous text.
// Move it into ctextfieldmt.cpp when it is reconstructed; delete this file with it.
#include "api/gui/ctextfieldmt.h"

namespace api {

void CTextFieldMT::Draw(IScreenMT&) const
{
    __builtin_trap();
}

} // namespace api
