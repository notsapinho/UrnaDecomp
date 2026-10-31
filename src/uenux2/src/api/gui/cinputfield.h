#pragma once

// api::CInputField<MASK> (/home/rubio/tse/uenux2/src/api/gui/cinputfield.h, the file the record of
// CInputField<CFramedText>::SetLength names, line 148, column 13). RTTI gives CInputField<CFramedText>, an si_class of
// IInputField<IScreen>, and the record gives the parameter's name, MASK; the parameter's being a type is what the
// record's `[MASK = api::CFramedText]` shows. The vtable is @1538760 and the mask lies at +64: fns 12402 and 12405 pass
// this + 64 to CFramedText's Move and Rect, and fn 2383 builds it there after IInputField's constructor (a 92-byte
// object). That constructor's parameters are read from fn 2383, their names are chosen, and no function of this tree's
// link holds it, as IInputField's cannot be reached.
//
// Draw (fn 12438) is written, and so are Rect and Move. GetTypeName (fn 12411) is a thunk of binaryen's fn 2904.
// SetLength (fn 12387) is the record's, a member defined in the class at line 148.

#include <memory>
#include <string>

#include "api/gui/iinputfield.h"
#include "api/gui/iscreen.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

class CFramedText;

/**
 * Campo de entrada na tela, com o texto digitado desenhado segundo uma máscara.
 */
template <typename MASK>
class CInputField : public IInputField<IScreen> {
public:
    CInputField(const std::shared_ptr<IInputValidation>& validation, size_t length, bool confirmaAoCompletar,
                bool corrigeLimpa, bool aceitaConfirma, bool aceitaBranco, bool corrigeSai, const SPoint& position,
                const SFont& font, ETextAlignment alignment)
        : IInputField<IScreen>(validation, length, confirmaAoCompletar, corrigeLimpa, aceitaConfirma, aceitaBranco,
                               corrigeSai),
          m_mask(length, position, font, alignment)
    {
    }

    void Draw(IScreen& screen) const override
    {
        m_mask.MaskText(screen, m_texto);

        if (m_ativo && !m_cursor && m_texto.size() != m_length) {
            m_mask.DrawFrame(m_texto.size(), static_cast<TColor>(1), screen);
        }
    }

    std::string GetTypeName() const override { return "CInputField"; }

    SRect Rect() const override { return m_mask.Rect(); }

    void Move(const SPoint& posicao) override
    {
        m_mask.Move(posicao);
        this->Invalidate();
    }

    // (original lines 61-144: content not recovered)
#line 145
    void SetLength(size_t length) override
    {
        if (length != this->m_length) {
            CPolySingleton<IScreen>::instance().FillRect(this->Rect(), static_cast<TColor>(1));
            m_mask.SetLength(length);
            IInputField<IScreen>::SetLength(length);
        }
    }
protected:
    MASK m_mask;
};

} // namespace api
