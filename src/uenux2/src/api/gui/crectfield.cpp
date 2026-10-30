// api::CRectField; the file is chosen, no record names it: see src/units/90-uenux2-api-gui.mk. This comment is the
// reconstruction's. Target functions of this file:
//   5501  CRectField(const SRect&, TColor)   out of line: the target keeps a body with two callers (fns 3680, 7787)
//   10960 Draw(IScreen&) const   calls IScreen slot 9, DrawRect in api/gui/iscreen.h, with a width of 1
//   5551  Rect() const           one body binaryen keeps for this class's and CFillField's
//   10959 GetTypeName() const    in the class
//   2783  Move(const SPoint&)    calls fn 1915, which has no name; in 90-uenux2-api-gui-pending.cpp

#include "api/gui/crectfield.h"

#include "api/gui/iscreen.h"

namespace api {

CRectField::CRectField(const SRect& rect, TColor cor)
    : m_rect(rect)
    , m_cor(cor)
{
}

void CRectField::Draw(IScreen& screen) const
{
    screen.DrawRect(m_rect, m_cor, 1);
}

SRect CRectField::Rect() const
{
    return m_rect;
}

} // namespace api
