// Pending members: the api::CProgressBar member src/uenux2/src/api/gui/cprogressbar.cpp does not hold yet. The class's
// vtable is emitted there with the destructor, its key function, and needs it defined; its body is NOT the target's, it
// traps. Target function, reached only through the vtable and named by its slot (the IFormField<IScreen> member the slot
// holds, api/gui/iformfield.h):
// - Draw 10977 (slot 2, 1914 B): it calls SRect::Left, Right and Adjust (fns 5488, 5487, 2768, primitives.cpp, written
//   and matched), the screen through its vtable, and fn 2677 twice: ecourna's copying CStringUtils::Replace (unit 00),
//   which copies a std::string and calls the in-place Replace (table slot 6413, fn 9407) on the copy through
//   invoke_viii. Draw passes it the label at +68, a two-character string ("%p", then "%v") and the percentage or the
//   value formatted with "{}". 2677 and 9407 match: Draw waits for nothing but its own body.
// GetTypeName (10975) is in cprogressbar.cpp now and matches, with 5075 (ASN1::AbstractData::getTypeName, with which
// binaryen once merged it) and 9696 still matched.
// Move each into cprogressbar.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cprogressbar.h"

namespace api {

void CProgressBar::Draw(IScreen&) const
{
    __builtin_trap();
}

} // namespace api
