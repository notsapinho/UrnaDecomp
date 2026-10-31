// api::CLineField (/home/rubio/tse/uenux2/src/api/gui/clinefield.cpp; the file is chosen, no record names it: see
// src/units/54-uenux2-clinefield.mk).
// Target functions of this file:
//   the constructor   no target function of its own: binaryen inlined it into fn 2244, api::CFormBuilder::AddLine
//   11067 Rect() const          (here)
//   11066 GetTypeName() const   (here)
//   12658 / 3681  ~CLineField() (complete / deleting; implicit, emitted with the vtable). The class's members are
//         trivially destructible, so its complete destructor is IFormFieldBase<IScreen>'s (12658), and the target's
//         deleting one (3681, shared with CFillField and CRectField) is a thunk into fn 1565, binaryen's one body for
//         eight such deleting destructors, which our link forms from this one and api::CLedFieldMT's (2777)
//   11068 Draw(IScreen&) const  (here: calls IScreen slot 8, DrawLine in api/gui/iscreen.h)
//   5527  Move(const SPoint&)   (here: one body binaryen shares with CTextFieldDoubleLine's)
// The definitions follow the target's link order: the uses-1 band 11066-11068 of ledger/ordinals.tsv gives Draw, Rect,
// GetTypeName. Move shares its body, so the band does not place it: after Rect is a choice.

#include "api/gui/clinefield.h"

#include <algorithm>

#include "api/gui/iform.h"
#include "api/gui/iscreen.h"

namespace api {

CLineField::CLineField(const SPoint& inicio, const SPoint& fim, TColor cor)
    : m_inicio(inicio)
    , m_fim(fim)
    , m_cor(cor)
{
}

void CLineField::Draw(IScreen& screen) const
{
    screen.DrawLine(m_inicio, m_fim, m_cor, 1);
}

SRect CLineField::Rect() const
{
    const TPosition x1 = m_inicio.x;
    const TPosition y1 = m_inicio.y;
    const TPosition x2 = m_fim.x;
    const TPosition y2 = m_fim.y;
    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
}

void CLineField::Move(const SPoint& posicao)
{
    if (posicao.x == m_inicio.x && posicao.y == m_inicio.y) {
        return;
    }

    const TPosition dx = posicao.x - m_inicio.x;
    const TPosition dy = posicao.y - m_inicio.y;

    m_fim.x += dx;
    m_fim.y += dy;
    m_inicio = posicao;

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

std::string CLineField::GetTypeName() const
{
    return "CLineField";
}

} // namespace api
