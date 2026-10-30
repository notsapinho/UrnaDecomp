// Pending members of api::CFillField, api::CRectField and api::CTextRectField: their sources in src/uenux2/src/api/gui/
// do not hold these yet. Each class's vtable (emitted with Draw, its key function, in the class's .cpp) needs them
// defined; their bodies are NOT the target's, they trap. Target functions:
//   2783  Move(const SPoint&), one body in slot 9 of all three vtables and CTextFieldMultiLine's: it calls fn 1915, which
//         has no name yet (it moves an SRect to a point keeping its size; it also has callers 2770, 10895, 10970, 10976)
//   10905 CTextRectField::Rect() const: record ctextrectfield.cpp:71:21; calls CPolySingleton<IScreen>'s instance (fn 512),
//         which has no name yet, to reach IScreen::GetFontMetrics
// Move each into its class's source when it is reconstructed; delete this file with the last one.
#include "api/gui/cfillfield.h"
#include "api/gui/crectfield.h"
#include "api/gui/ctextrectfield.h"

namespace api {

void CFillField::Move(const SPoint&)
{
    __builtin_trap();
}

void CRectField::Move(const SPoint&)
{
    __builtin_trap();
}

void CTextRectField::Move(const SPoint&)
{
    __builtin_trap();
}

SRect CTextRectField::Rect() const
{
    __builtin_trap();
}

} // namespace api
