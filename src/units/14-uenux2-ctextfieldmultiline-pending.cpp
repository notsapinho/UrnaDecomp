// Pending members: the api::CTextFieldMultiLine members src/uenux2/src/api/gui/ctextfieldmultiline.cpp does not hold
// yet. The class's vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's,
// they trap. Target functions: Draw 10925, Rect 10924, and GetTextLines 5497, which the two call (declared, not defined
// here; its record is 116:21). These stay traps because the real body costs matches, as measured: GetTextLines, written with
// std::getline over a std::istringstream as 5497's rows read, gives this uenux2 object an instance of std::getline, which
// links ahead of app/asn1/AVNDecoder.o, whose copy is the target's. fns 1917, 2649, 5055, 8877, 8878, 8883 and 8884 then
// leave `match`, for 10924 alone at `unresolved`. So they wait for that instance to be the target's. With the three written,
// Rect scored 3 over 151 rows, all operand-only, and Draw 17 over 276, the height's load at the loop's test; 5497 scored 578
// over 1051: the target holds the stream's constructor inline, and our link keeps it in app/roots_rhvoice.o.
// Move each into ctextfieldmultiline.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfieldmultiline.h"

namespace api {

void CTextFieldMultiLine::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CTextFieldMultiLine::Rect() const
{
    __builtin_trap();
}

} // namespace api
