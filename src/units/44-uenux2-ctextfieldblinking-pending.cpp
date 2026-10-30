// Pending members: the api::CTextFieldBlinking members src/uenux2/src/api/gui/ctextfieldblinking.cpp does not hold yet.
// Every virtual member the class declares is pending and its destructor is implicit (the deleting destructor, target
// fn 10941, holds the base-object one's body inlined), so the class's key function is Draw, the first it declares, and
// the vtable is emitted here. With it this object emits what the vtable names that the class declares implicitly: the
// destructors (target fns 10942 and 10941, slots 0 and 1), the compiler's code for the class definition in
// api/gui/ctextfieldblinking.h, not stand-ins; they move to ctextfieldblinking.o with the vtable when Draw does. The
// bodies below are NOT the target's, they trap. Target functions, by vtable slot (vtable @1582448; ledger/vtables.json),
// and what each waits for:
//   2  10946  Draw(IScreen&) const: draws through the IScreen slot at +76, which api/gui/iscreen.h does not declare
//   3  10945  Show(): m_timer's slot 2 (+8), 4  10944  Hide(): m_timer's slot 3 (+12): api::ITimer has no header here
//             (api/util/itimer.h is round DECOMP3 lane K's), so the class only forward-declares it
//   7  10940  GetTypeName() const: builds "CTextFieldBlinking" through fn 3891, which has no name yet
//   8  10943  Rect() const (record ctextfieldblinking.cpp:70:21): calls fn 3889, which has no name yet
//   9  2241   Move(const SPoint&): binaryen's one body for CImageField, CDSImageField, CImageFieldUpdate, CTextField,
//             CTextFieldUpdate and this class; it reads api::IForm<IScreen>, and api/gui/iform.h is stub-only
// Slots 5 and 6 are IFormFieldBase<IScreen>'s Refresh and SetForm (fns 4118, 3037), inherited. Move each member into
// ctextfieldblinking.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfieldblinking.h"

namespace api {

void CTextFieldBlinking::Draw(IScreen&) const
{
    __builtin_trap();
}

void CTextFieldBlinking::Show()
{
    __builtin_trap();
}

void CTextFieldBlinking::Hide()
{
    __builtin_trap();
}

std::string CTextFieldBlinking::GetTypeName() const
{
    __builtin_trap();
}

SRect CTextFieldBlinking::Rect() const
{
    __builtin_trap();
}

void CTextFieldBlinking::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
