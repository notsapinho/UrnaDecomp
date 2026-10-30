// Reconstruction's note, not TSE's text. The file's records are the constructor's, line 28, and MaskText's, line 66,
// which are not written, so both lines stay blank. Rect, Move and DrawFrame have no record: that they are in this file,
// and their lines, are chosen (src/units/92-uenux2-iinputfield.mk).
#include <algorithm>

#include "api/gui/cframedtext.h"
#include "api/gui/iscreen.h"

namespace api {

// (original lines 11-24: content not recovered)
#line 25
// <stubs>
// f1385 · 260 B · unmatched · name unknown
// ? f1385(i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 30-62: content not recovered)
#line 63
// <stubs>
// f2780 · 766 B · unmatched · name unknown
// void f2780(i32, i32, i32) { ... }
// </stubs>













SRect CFramedText::Rect() const
{
    const TPosition x1 = m_position.x;
    const TPosition y1 = m_position.y;
    const TPosition x2 = x1 + Largura();
    const TPosition y2 = y1 + m_altura;
    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
}

void CFramedText::Move(const SPoint& position)
{
    m_position = position;
}

void CFramedText::DrawFrame(size_t index, TColor color, IScreen& screen) const
{
    screen.DrawRect(CellRect(index), color, 1);
}

} // namespace api
