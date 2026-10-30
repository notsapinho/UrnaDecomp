// api::CFillField; the file is chosen, no record names it: see src/units/90-uenux2-api-gui.mk. This comment is the
// reconstruction's. Target functions of this file:
//   the constructor   no target function of its own: fn 2245 holds it inlined, and its bytes do not say which inliner did
//                     it. Out of line is chosen, as CRectField's is (fn 5501)
//   11142 Draw(IScreen&) const   calls IScreen slot 6, FillRect in api/gui/iscreen.h
//   5551  Rect() const           one body binaryen keeps for this class's and CRectField's
//   11141 GetTypeName() const    in the class
//   2783  Move(const SPoint&)    calls fn 1915, which has no name; in 90-uenux2-api-gui-pending.cpp

#include "api/gui/cfillfield.h"

#include "api/gui/iscreen.h"

namespace api {

CFillField::CFillField(const SRect& rect, TColor cor)
    : m_rect(rect)
    , m_cor(cor)
{
}

void CFillField::Draw(IScreen& screen) const
{
    screen.FillRect(m_rect, m_cor);
}

SRect CFillField::Rect() const
{
    return m_rect;
}

} // namespace api
