#pragma once

#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

/**
 * Campo de texto de uma linha, escrito a partir de uma posição da tela.
 */
class CTextField : public IFormField<IScreen> {
public:
    CTextField(const SPoint& posicao, const SharedIText& text, const SFont& font, TColor corTexto, TColor corFundo);

    std::string GetTypeName() const override;

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

    // The text's colour (+44, the constructor's corTexto): vota::CMostraQRCodeBU::AjustaTela (target fn 5982) calls fn
    // 940 on the fields FindFieldAs<CTextField> gives it, the body of CTextBox::SetStatus, which stores +44 when it
    // differs and refreshes the form. The member, its name and its being out of line beside Move are chosen.
    void SetCorTexto(TColor cor);

private:
    SPoint m_posicao;
    SharedIText m_text;
    SFont m_font;
    TColor m_corTexto;
    TColor m_corFundo;
    // the area of the last drawing and whether the next one erases it first: Draw (target fn 10952) fills
    // m_rectDesenhado with m_corFundo when m_apagar is true, stores the rectangle of the text it writes there and sets
    // m_apagar to false. The names (and every member name here) are chosen: no evidence gives them
    mutable SRect m_rectDesenhado;
    mutable bool m_apagar = false;
};

} // namespace api
