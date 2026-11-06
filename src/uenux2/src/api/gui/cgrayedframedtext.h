#pragma once

// api::CGrayedFramedText: RTTI gives an si_class of CFramedText, vtable @1578744, whose slot is MaskText (fn 5534,
// record cgrayedframedtext.cpp 29:15). fn 5535 is the constructor, which calls CFramedText's with the font @474880
// ({40, 0}, ctelasvota.cpp's FONTE_NUMERO) and the alignment 0: parameters its two target callers (fns 3060 and 4185)
// pass alike, folded by binaryen's dead-argument elimination (src/units/378-uenux2-ctelasvota-criatela.mk). The
// header's path, beside the recorded .cpp, and the parameters' names are chosen. Both members are written in
// cgrayedframedtext.cpp.

#include "api/gui/cframedtext.h"

namespace api {

/**
 * Máscara de células emolduradas sobre fundo cinza.
 */
class CGrayedFramedText : public CFramedText {
public:
    CGrayedFramedText(size_t length, const SPoint& position, const SFont& font, ETextAlignment alignment);

    void MaskText(IScreen& screen, const std::string& text) const override;
};

} // namespace api
