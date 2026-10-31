// Pending members of unit 92: the virtual members src/uenux2/src/api/gui/cframedtext.cpp and api/gui/cinputfield.h do not
// hold yet. The bodies below are NOT the target's, they trap. Target functions:
//   2780  CFramedText::MaskText(IScreen&, const std::string&) const, record cframedtext.cpp 66:15, the class's key function,
//         so this object emits its vtable: calls fn 5537, the drawing of one cell, which inlines api::SRect::Top and
//         Bottom (records api/gui/primitives.cpp 26:37 and 38:37) and calls fns 5488 and 5487 (unit 108's, matched)
//   5534  CGrayedFramedText::MaskText(IScreen&, const std::string&) const, record cgrayedframedtext.cpp 29:15: calls fns 5536
//         and 5537, not written, and DrawFrame
// binaryen inlines a trap into a direct caller and the rest of the caller goes, so the Draws that call MaskText directly
// (fns 12438, 12593, 12708) are written and hold no code of their own until these land.
// Each moves to its source when it is reconstructed; delete this file with the last one.
#include "api/gui/cframedtext.h"
#include "api/gui/cgrayedframedtext.h"
#include "api/gui/cinputfield.h"

namespace api {

void CFramedText::MaskText(IScreen&, const std::string&) const
{
    __builtin_trap();
}

void CGrayedFramedText::MaskText(IScreen&, const std::string&) const
{
    __builtin_trap();
}

} // namespace api
