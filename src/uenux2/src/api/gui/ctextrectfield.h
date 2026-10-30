#pragma once

// api::CTextRectField (/home/rubio/tse/uenux2/src/api/gui/ctextrectfield.cpp names its file: the records of the
// constructor, line 51, column 15, and of Rect, line 71, column 21; the header beside it is chosen). RTTI: an si_class of
// api::IFormField<api::IScreen>. The layout is what the constructor (inlined into fn 5546, a 12 + 68 B std::make_shared
// block), the destructors (fns 10904, 10903, thunks into binaryen's 6022, 6021) and Draw (fn 10906) give: +24 the SRect
// the text is written in, +32 the first TColor of the record, +36/+40 the SharedIText, +44 the SFont, +52 the second
// TColor, +56 the area of the last drawing, +64 a byte the constructor sets to 1 and only Draw reads. Draw passes the
// +52 colour to IScreen's slot 20 as the text's and the +32 colour as the background's. Every member and parameter name
// is chosen: no evidence gives them. The destructors are implicit: 6021 holds 6022's body inlined. GetTypeName is
// in the class: the uses-1 band 10902-10906 of ledger/ordinals.tsv puts it after the destructors, which come after Draw
// and Rect. The comments are ours, not TSE's.

#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

class CTextRectField : public IFormField<IScreen> {
public:
    CTextRectField(const SRect& rect, TColor corFundo, const SharedIText& text, const SFont& font, TColor corTexto);

    void Draw(IScreen& screen) const override;

    std::string GetTypeName() const override { return "CTextRectField"; }

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    SRect m_rect;
    TColor m_corFundo;
    SharedIText m_text;
    SFont m_font;
    TColor m_corTexto;
    mutable SRect m_rectDesenhado;
    bool m_preencher = true;
};

} // namespace api
