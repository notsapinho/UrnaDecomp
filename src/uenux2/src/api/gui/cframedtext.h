#pragma once

// api::CFramedText and its layout. RTTI names the class, polymorphic with no base, and its vtable (@1578692) has one
// slot, MaskText (fn 2780, record cframedtext.cpp 66:15): no virtual destructor. The header's path, beside the recorded
// .cpp, is chosen. The constructor's record (cframedtext.cpp 28:24) gives its parameters, and its body (fn 1385) the
// layout:
//   +4 the length, +8 the position, +12 the font, +20 the alignment, +24 and +25 two bytes slot 2 of IScreen fills,
//   which are a cell's width and height, and which fn 1385 then grows by a gap. The names of the data members are
//   chosen.
//
// Rect, Move and DrawFrame (fns 3677, 3676, 2779) have no record: their names and their being members are chosen from
// what they read and from their callers, and 2779's parameter types as far as its body uses them
// (docs/how-to-decompile.md step 3). CellRect holds what fns 2779, 2780, 5536 and 5537 inline; Espaco and Largura what
// fn 1385 and those inline. All three names are chosen. Their spelling is the part the bytes decide:
// - Espaco reads the quotient into a local and tests that: `i32.div_s` with the test on the size, with no extend16 and
//   no shift, comes from that form. `std::max(size / 8, 1)` (compares the quotient) and `size < 8 ? 1 : size / 8`
//   (`std::max(size, 8) >> 3`) compile to other code. A TPosition local gives the same functions; the int is chosen.
// - CellRect and Rect read locals and build the SRect as CLineField::Rect does. Reading m_position in place gives the
//   same functions, and `std::minmax` does not. CellRect with `inline` gives the same, as does Largura returning int.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>

#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

/**
 * Máscara que desenha um texto em células emolduradas.
 */
class CFramedText {
public:
    CFramedText(size_t length, const SPoint& position, const SFont& font, ETextAlignment alignment);

    virtual void MaskText(IScreen& screen, const std::string& text) const;

    SRect Rect() const;

    void Move(const SPoint& position);

    void DrawFrame(size_t index, TColor color, IScreen& screen) const;

protected:
    int Espaco() const
    {
        const int espaco = m_font.size / 8;
        return espaco > 0 ? espaco : 1;
    }

    TPosition Largura() const { return (m_length - 1) * Espaco() + m_length * m_largura; }

    SRect CellRect(size_t index) const
    {
        const TPosition x1 = m_position.x + index * (m_largura + Espaco());
        const TPosition y1 = m_position.y;
        const TPosition x2 = x1 + m_largura;
        const TPosition y2 = y1 + m_altura;
        return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
    }

    size_t m_length;
    SPoint m_position;
    SFont m_font;
    ETextAlignment m_alignment;
    uint8_t m_largura;
    uint8_t m_altura;
};

} // namespace api
