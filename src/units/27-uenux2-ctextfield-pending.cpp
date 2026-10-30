// Pending members: the api::CTextField members src/uenux2/src/api/gui/ctextfield.cpp does not hold yet. The class's
// vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's, they trap.
// Target functions: Draw 10952 (calls IScreen slots at +24 and +76, which api/gui/iscreen.h does not declare yet),
// Rect 10951 (record ctextfield.cpp:55:21; calls fn 3889, which has no name yet) and Move 2241 (binaryen's one body for
// CImageField, CDSImageField, CImageFieldUpdate, CTextFieldBlinking, CTextFieldUpdate and this class).
// Move each into ctextfield.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfield.h"

namespace api {

void CTextField::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CTextField::Rect() const
{
    __builtin_trap();
}

void CTextField::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
