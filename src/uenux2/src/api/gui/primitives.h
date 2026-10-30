#pragma once

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
};

struct SFont {
    TFontSize size;
    int style;
};

} // namespace api
