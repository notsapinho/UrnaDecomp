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

    SPoint() = default;

    // the point of two coordinates, a constructor rather than the aggregate's initialization. Evidence: the target
    // evaluates both coordinates before it stores the first, where SPoint(x, y) of the aggregate stores x before it
    // computes y. Measured in the whole link: in api::CInteractiveFormBuilder::AddLabeledInputControl (target fn 653)
    // the line's first point loads area.bottom before area.left with this constructor and after it without, the one
    // row that is no operand in 653's score without it; api::CFormBuilder::GetLabeledKeyPos (fn 5544) matches with
    // `return SPoint(...)` through it, where the aggregate needed a temporary assigned to a named result. Of the 611
    // objects compiled with it and without it, five differ (cinteractiveformbuilder.cpp's, cformbuilder.cpp's,
    // cstepsprogressbar.cpp's, cvalidaidentidade.cpp's and unit 31's roots), and no match left
    // (src/units/120-uenux2-iform.mk). It moves two written functions that do not match:
    // vota::CValidaIdentidade::StartState (fn 10627, unit 278) reads its options' numbers before it stores the
    // point's x, as the target does, 149 over 1740 rows -> 144 over 1739; api::CStepsProgressBar::Draw (fn 5504, unit
    // 41) stores the text point Recalcula computes as one 32-bit word, where the target has the two 16-bit stores the
    // aggregate gives, 1162 over 5684 rows -> 1196 over 5696 (pnpm wasm score). The parameter names and constexpr are
    // chosen; the defaulted constructor keeps SPoint{} and a default-constructed point all zero
    constexpr SPoint(TPosition x_, TPosition y_)
        : x(x_)
        , y(y_)
    {
    }
};

struct SRect {
    TPosition left = 0;
    TPosition top = 0;
    TPosition right = 0;
    TPosition bottom = 0;

    // keeps SRect{} and a default-constructed rectangle all zero, as the aggregate's were
    SRect() = default;

    // the rectangle of two opposite corners, in any order. Evidence that the original normalizes wherever it builds a
    // rectangle: 27 target functions store a pair of min/max corners (`select` results stored by `i32.store16` at two
    // offsets 4 apart), and vota's and comum's 12040, 12055 and 7787, far from api/gui, normalize rectangles whose
    // corners are constants and the screen's size, which no programmer orders by hand: (10, 95, w - 30, h - 130),
    // (10, 95, 230, h - 115) and (80, 100, w - 80, h - 200). A normalizing constructor explains all of them. Fn 5506
    // (CStepsProgressBar's Divide, cstepsprogressbar.cpp) builds each area with std::vector<SRect>::emplace_back and
    // narrows the int corner x + l - 1 to TPosition in emplace_back's fast and slow paths both, after a zero extension
    // of each operand (two `i32.and 65535`); fn 10971 holds the same loop. Measured on cstepsprogressbar.cpp's object:
    // emplace_back of the four corners through this constructor gives those two masks, and Divide matches with it;
    // SRect::Normalized in the argument stores the area as one 64-bit word, and std::min and std::max written in the
    // arguments narrow the corner once, with no mask. constexpr is measured too: without it the brace-initialized
    // static CApplication::s_areaTela (capplication.cpp) leaves .data for .bss and a store in that file's static
    // constructor, where the target holds its bytes as data. The parameter names are chosen. With it SRect is no
    // aggregate, so a brace form of four values calls it: of the 929 objects the tree compiles, compared byte for byte
    // with the build before it, only cstepsprogressbar.cpp's (whose source changed too) and the stand-ins of units 14,
    // 31 and 90 differ, the stand-ins because their corners are not known to be in order and are now normalized
    constexpr SRect(TPosition x1, TPosition y1, TPosition x2, TPosition y2)
        : left(std::min(x1, x2))
        , top(std::min(y1, y2))
        , right(std::max(x1, x2))
        , bottom(std::max(y1, y2))
    {
    }

    // right and left both count: api::CTextBox::Draw (target fn 10958) centres on this value, and api::CTextFieldUpdate::Draw
    // and api::CTextRectField::Draw (fns 10916, 10906) compare it with 1. The member, its name and its sign are chosen
    TPosition Width() const { return right - left + 1; }

    // the same rectangle by value, which the landed bodies call. The name and its being a static member are chosen: the
    // target's code shows the normalization the constructor above gives (its comment has the evidence), and this one's
    // callers' objects are unchanged since it came
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
