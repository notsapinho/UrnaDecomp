#pragma once

// api::CGrayedFramedText: RTTI gives an si_class of CFramedText, vtable @1578744, whose slot is MaskText (fn 5534,
// record cgrayedframedtext.cpp 29:15). fn 5535 is the constructor, which calls CFramedText's with a fixed font and
// alignment 0. The header's path, beside the recorded .cpp, and the parameters' names are chosen. MaskText is written in
// cgrayedframedtext.cpp; the constructor is not (src/units/92-uenux2-iinputfield.mk says what it waits for).

#include "api/gui/cframedtext.h"

namespace api {

/**
 * Máscara de células emolduradas sobre fundo cinza.
 */
class CGrayedFramedText : public CFramedText {
public:
    CGrayedFramedText(size_t length, const SPoint& position);

    void MaskText(IScreen& screen, const std::string& text) const override;
};

} // namespace api
