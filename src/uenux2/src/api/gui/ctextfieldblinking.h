#pragma once

// api::CTextFieldBlinking: the class is named by RTTI (an si_class of api::IFormField<api::IScreen>,
// ledger/classes.json), the constructor and Rect by their records (ctextfieldblinking.cpp:39:15 and 42:15, :70:21).
// The header's name and the member names are chosen. The layout (68 bytes, after the 12 of the control block in the
// 80-byte std::make_shared block of target fn 1265) is read from the constructor, which binaryen inlined into that one
// caller, from the destructor (10942) and from Draw (10946), Show (10945) and Hide (10944). The constructor creates
// m_timer through ITimerScheduler::GetInst() with a 500 ms period and a callback (10937) that toggles m_aceso and
// redraws the field through its form; Draw writes the text in m_corTexto while m_aceso is true and in m_corPisca
// otherwise, over m_corFundo; Show and Hide start and stop the timer. The constructor throws when the text is null
// (line 39) or when the two text colours are equal (line 42).

#include <memory>
#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;
class ITimer;

/**
 * Campo de texto de uma linha que pisca: o texto alterna entre duas cores enquanto o campo está visível.
 */
class CTextFieldBlinking : public IFormField<IScreen> {
public:
    CTextFieldBlinking(const SPoint& posicao, const SharedIText& text, const SFont& font, TColor corTexto,
                       TColor corPisca, TColor corFundo);

    void Draw(IScreen& screen) const override;

    void Show() override;

    void Hide() override;

    std::string GetTypeName() const override { return "CTextFieldBlinking"; }

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    SPoint m_posicao;
    SharedIText m_text;
    SFont m_font;
    TColor m_corTexto;
    TColor m_corPisca;
    TColor m_corFundo;
    std::shared_ptr<ITimer> m_timer;
    bool m_aceso = true;
};

} // namespace api
