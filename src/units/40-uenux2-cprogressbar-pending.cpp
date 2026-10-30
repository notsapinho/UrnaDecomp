// Pending members: the api::CProgressBar members src/uenux2/src/api/gui/cprogressbar.cpp does not hold yet. The
// class's vtable is emitted there with the destructor, its key function, and needs them defined; their bodies are NOT
// the target's, they trap. Target functions, all three reached only through the vtable and named by their slot (the
// IFormField<IScreen> member each slot holds, api/gui/iformfield.h):
// - Draw 10977 (slot 2, 1914 B): calls the SRect setters 5487 and 5488 (api/gui/primitives.cpp, not reconstructed),
//   fn 2768 (the rect moved in by an offset, no name), fn 2677 (no name) and the screen through its vtable;
// - Move 10976 (slot 9, 97 B): moves the rect at +36 through fn 1915 (no name) and marks the form to redraw;
// - GetTypeName 10975 (slot 7, 61 B): `return "CProgressBar";` in cprogressbar.cpp compiles to the target's body, but
//   binaryen's merge-similar-functions then folds it with our copy of the inline ASN1::AbstractData::getTypeName
//   (src/asn1/asn1.h, target fn 5075, which returns the 12-character "AbstractData" the same way) into one shared body
//   and two thunks. The target's 5075 calls the std::string constructor (fn 148) instead and is not merged, and ours
//   is `differs` (splat/scan.tsv); GetTypeName waits for that copy to be the target's.
// Move each into cprogressbar.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/cprogressbar.h"

namespace api {

void CProgressBar::Draw(IScreen&) const
{
    __builtin_trap();
}

void CProgressBar::Move(const SPoint&)
{
    __builtin_trap();
}

std::string CProgressBar::GetTypeName() const
{
    __builtin_trap();
}

} // namespace api
