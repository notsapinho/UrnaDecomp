#pragma once

// api::CTextFieldMultiLine (/home/rubio/tse/uenux2/src/api/gui/ctextfieldmultiline.cpp). Draw is the first virtual
// member defined out of line, so it is the key function and that .cpp emits the vtable. Inside the uses-1 band of
// ledger/ordinals.tsv the index runs against the link order: Draw (10925), Rect (10924), the D2 (10923), the D0 (10922),
// then GetTypeName (10921). The destructors are implicit (the D0 holds the D2's body), so they are emitted with the
// vtable at the end of the TU, and GetTypeName, after them, is inline too: it is written in the class (a reading of the
// band, as api/gui/ctextbox.h reads its own). The data members' names are chosen, as no evidence gives them, and the
// comments are ours, not TSE's.

#include <string>
#include <vector>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

/**
 * Campo de texto que quebra o texto em várias linhas dentro de um retângulo.
 */
class CTextFieldMultiLine : public IFormField<IScreen> {
public:
    CTextFieldMultiLine(const SRect& rect, const SharedIText& text, const SFont& font, TColor corTexto, TColor corFundo);

    std::string GetTypeName() const override { return "CTextFieldMultiLine"; }

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    std::vector<std::string> GetTextLines() const;

    SRect m_rect;
    mutable SRect m_rectDesenhado;
    mutable bool m_desenhado = false;
    SharedIText m_text;
    SFont m_font;
    TColor m_corTexto;
    TColor m_corFundo;
    TPosition m_alturaLinha;
};

} // namespace api
