// api::CLineField (/home/rubio/tse/uenux2/src/api/gui/clinefield.cpp; the file is chosen, no record names it: see
// src/units/54-uenux2-clinefield.mk).
// Target functions of this file:
//   11067 Rect() const          (here)
//   11066 GetTypeName() const   (here)
//   12658 / 3681  ~CLineField() (complete / deleting; implicit, emitted with the vtable). The class's members are
//         trivially destructible, so its complete destructor is IFormFieldBase<IScreen>'s (12658), and the target's
//         deleting one (3681, shared with CFillField and CRectField) is a thunk into fn 1565, binaryen's one body for
//         eight such deleting destructors, which our link forms from this one and api::CLedFieldMT's (2777)
//   11068 Draw(IScreen&) const  (pending: calls IScreen slot 8, which api/gui/iscreen.h does not declare yet)
//   5527  Move(const SPoint&)   (pending: one body binaryen shares with CTextFieldDoubleLine's; reads IForm<IScreen>)
// The pending members are defined in src/units/54-uenux2-clinefield-pending.cpp. The definitions follow the target's
// link order: ledger/ordinals.tsv gives Draw, Rect and GetTypeName the ordinals 4193, 4194 and 4195.

#include "api/gui/clinefield.h"

#include <algorithm>

namespace api {

SRect CLineField::Rect() const
{
    const TPosition x1 = m_inicio.x;
    const TPosition y1 = m_inicio.y;
    const TPosition x2 = m_fim.x;
    const TPosition y2 = m_fim.y;
    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
}

std::string CLineField::GetTypeName() const
{
    return "CLineField";
}

} // namespace api
