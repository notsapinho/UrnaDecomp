// Reconstruction's note, not TSE's text. The file's one record is api::CGrayedFramedText::MaskText's throw, line 29
// (fn 5534); its other lines are chosen. The constructor (fn 5535) passes CFramedText's constructor the font and the
// alignment its callers give, both folded in the target (src/units/378-uenux2-ctelasvota-criatela.mk).
#include "api/gui/cgrayedframedtext.h"

#include <string>

#include "api/gui/eueguierror.h"
#include "api/gui/iscreen.h"

namespace api {

// (original lines 13-19: content not recovered)
#line 20
CGrayedFramedText::CGrayedFramedText(size_t length, const SPoint& position, const SFont& font, ETextAlignment alignment)
    : CFramedText(length, position, font, alignment)
{
}


void CGrayedFramedText::MaskText(IScreen& screen, const std::string& text) const
{
    if (text.size() > m_length) {
        throw CUeGuiError(EUE_GUI_GRAYEDFRAMEDTEXT_TEXTO_GRANDE_DEMAIS, "Texto [" + text + "] eh grande demais");
    }

    for (size_t i = 0; i < text.size(); ++i) {
        FillCell(i, static_cast<TColor>(1), screen);
        DrawChar(i, text[i], static_cast<TColor>(2), screen);
        DrawFrame(i, static_cast<TColor>(3), screen);
    }
    for (size_t i = text.size(); i < m_length; ++i) {
        FillCell(i, static_cast<TColor>(5), screen);
        DrawFrame(i, static_cast<TColor>(2), screen);
    }
}

} // namespace api

// <stubs>
// f5535 · 25 B · unmatched · placement: link order · name unknown
// void f5535(i32, i32, i32) { ... }
// </stubs>
