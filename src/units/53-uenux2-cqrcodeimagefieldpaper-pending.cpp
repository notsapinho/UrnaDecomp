// Pending members: the api::CQRCodeImageFieldPaper member no source holds yet. Draw is the class's only virtual member
// defined out of line (its key function), so the vtable is emitted here, and with it what the vtable names that the
// class declares implicitly or inherits inline: the destructors (target fns 10962, 10961), IFormFieldBase<IPaper>'s
// Show, Hide, Refresh and SetForm, and IFormField<IPaper>::GetTypeName (11014, inline in api/gui/iformfield.h). Those
// are the compiler's code for the class definition (api/gui/cqrcodeimagefieldpaper.h), not stand-ins; they move to
// cqrcodeimagefieldpaper.cpp's object with the vtable when Draw lands there.
// Draw's body is NOT the target's, it traps. Target function: Draw 10963 (30 B), which calls slot 12 of the IPaper it
// is given with the QR code's image, side and scale (this+24, +36, +40); IPaper has no header with that slot yet.
// Move it into src/uenux2/src/api/gui/cqrcodeimagefieldpaper.cpp when it is reconstructed; delete this file with it.
#include "api/gui/cqrcodeimagefieldpaper.h"

namespace api {

void CQRCodeImageFieldPaper::Draw(IPaper&) const
{
    __builtin_trap();
}

} // namespace api
