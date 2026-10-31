#pragma once

#include <algorithm>
#include <cstdint>

namespace api {

using TPosition = int16_t;
using TFontSize = int16_t;

enum TColor : int {};

struct SPoint {
    TPosition x = 0;
    TPosition y = 0;
};

struct SRect {
    TPosition left = 0;
    TPosition top = 0;
    TPosition right = 0;
    TPosition bottom = 0;

    // right and left both count: api::CTextBox::Draw (target fn 10958) centres on this value, and api::CTextFieldUpdate::Draw
    // and api::CTextRectField::Draw (fns 10916, 10906) compare it with 1. The member, its name and its sign are chosen
    TPosition Width() const { return right - left + 1; }

    // the rectangle of two opposite corners, in any order. The target writes the min and max at every site, so it may
    // be a constructor of the original; SRect stays an aggregate here because the brace forms of the landed bodies
    // keep their order that way. The name is chosen
    static SRect Normalized(TPosition x1, TPosition y1, TPosition x2, TPosition y2)
    {
        return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
    }

    // the setters of one edge (records primitives.cpp 20, 26, 32 and 38, which name them and their parameter type): each
    // asserts first that the edge does not pass the opposite one (api/util/eueasserterror.h), and the parameters' names are
    // the ones the asserts' texts spell. Left (fn 5488) and Right (fn 5487) are written; Top and Bottom, which binaryen
    // inlined into fn 5537, are not
    void Left(TPosition l);
    void Top(TPosition t);
    void Right(TPosition r);
    void Bottom(TPosition b);

    // to a new top-left corner, keeping the size: target fn 1915, in primitives.cpp. The name is chosen
    void Move(const SPoint& posicao);

    // the same along x only: CTextBox::Rect (fn 10956) holds it, a load of left after its value was stored, which binaryen
    // inlining its one caller gives and clang inlining does not. The name is chosen
    void MoveX(TPosition x);

    // the smallest rectangle that holds this one and @p outro: target fn 1916, in primitives.cpp. The name is chosen
    SRect Union(const SRect& outro) const;

    // this one with each edge moved by its own amount, in order again: target fn 2768, in primitives.cpp. The name is chosen
    SRect Adjust(TPosition dLeft, TPosition dTop, TPosition dRight, TPosition dBottom) const;
};

struct SFont {
    TFontSize size;
    int style;
};

} // namespace api
