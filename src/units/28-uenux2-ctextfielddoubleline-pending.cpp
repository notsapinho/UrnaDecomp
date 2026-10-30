// Pending members: the api::CTextFieldDoubleLine members src/uenux2/src/api/gui/ctextfielddoubleline.cpp does not hold
// yet. The class's vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's,
// they trap. Target functions: Draw 10931 and Rect 10929 (which inlines CalcLineRect, record 133:21), both calling
// GetTextLines 5499 (record 68:21; declared, not defined here, and not reconstructed: it keeps its stub), and Move
// 5527 (binaryen's one body for CLineField and this class).
// Move each into ctextfielddoubleline.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfielddoubleline.h"

namespace api {

void CTextFieldDoubleLine::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CTextFieldDoubleLine::Rect() const
{
    __builtin_trap();
}

void CTextFieldDoubleLine::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
