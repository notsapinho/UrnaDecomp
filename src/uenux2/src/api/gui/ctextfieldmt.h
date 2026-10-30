#pragma once

// api::CTextFieldMT: the class is named by RTTI (an si_class of api::IFormField<api::IScreenMT>, ledger/classes.json),
// the constructor by its record (ctextfieldmt.cpp:25:15). The header's name and the member names are chosen; the layout
// (48 bytes, the size every caller allocates) is read from the constructor (target fn 1262), the destructor (10933) and
// Draw (10934): Draw erases the text it drew last when the new one is shorter, draws the current one, and keeps both
// the text and the position it drew.

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreenMT;

/**
 * Campo de texto de uma linha desenhado na tela MT.
 */
class CTextFieldMT : public IFormField<IScreenMT> {
public:
    CTextFieldMT(const SPoint& posicao, const SharedIText& text);

    void Draw(IScreenMT& screen) const override;

private:
    SPoint m_posicao;
    SharedIText m_text;
    mutable SharedIText m_textDesenhado;
    mutable SPoint m_posicaoDesenhada;
};

} // namespace api
