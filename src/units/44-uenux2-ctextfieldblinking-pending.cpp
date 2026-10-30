// Pending members: the api::CTextFieldBlinking members src/uenux2/src/api/gui/ctextfieldblinking.cpp does not hold yet.
// The class's vtable (emitted with Draw, its key function, in that TU, with the implicit destructors) needs them defined;
// their bodies are NOT the target's, they trap. Target functions, by vtable slot (vtable @1582448; ledger/vtables.json),
// and what each waits for:
//   7  10940  GetTypeName() const: builds "CTextFieldBlinking" through fn 3891, which has no name yet
//   8  10943  Rect() const (record ctextfieldblinking.cpp:70:21): calls fn 3889, which has no name yet
// Slots 5 and 6 are IFormFieldBase<IScreen>'s Refresh and SetForm (fns 4118, 3037), inherited. Move each member into
// ctextfieldblinking.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfieldblinking.h"

namespace api {

std::string CTextFieldBlinking::GetTypeName() const
{
    __builtin_trap();
}

SRect CTextFieldBlinking::Rect() const
{
    __builtin_trap();
}

} // namespace api
