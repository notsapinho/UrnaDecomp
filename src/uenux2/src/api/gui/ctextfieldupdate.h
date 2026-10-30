#pragma once

// api::CTextFieldUpdate (/home/rubio/tse/uenux2/src/api/gui/ctextfieldupdate.h; the header's name is the class's, no
// record names it). RTTI: an si_class of IFormField<IScreen> (ledger/classes.json), 80 bytes (its callers 502, 3058
// and 5936 make_shared it with f137(92): the 12-byte control block and the object). The layout is what the bodies
// give: the constructor (fn 3658) stores the position at +24, the SharedIText at +28, the SFont at +36 and the two
// colours at +44 and +48 (the record's parameter order), the string at +52 and the rectangle at +64 start empty, and
// +72 receives the timer that slot 0 of ITimerScheduler::GetInst() (fn 1259, record itimerscheduler.cpp:23:12) creates
// with the interval and a lambda; Draw (fn 10916) erases +64 with +48 when it is not empty, draws the text at +24 with
// +36, +44 and +48, stores the drawn rectangle at +64 and the text it drew at +52; Show and Hide (fns 10915, 10914)
// call slots 2 and 3 of the timer; the destructor (fn 5495) releases +72, +52 and +28 in that order. The member names
// are chosen; the timer's type is only declared here: no header of ours defines it yet (simulador::CWasmTimer and
// api::CTimer, the classes the schedulers create, derive from api::ITimer, ledger/classes.json).

#include <chrono>
#include <memory>
#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;
class ITimer;

/**
 * Campo de texto de uma linha que se atualiza sozinho: um timer relê o texto a cada intervalo e o campo é redesenhado
 * quando ele muda.
 */
class CTextFieldUpdate : public IFormField<IScreen> {
public:
    CTextFieldUpdate(const SPoint& posicao, const SharedIText& text, const std::chrono::milliseconds& intervalo, const SFont& font,
                     TColor corTexto, TColor corFundo);

    ~CTextFieldUpdate() override;

    void Draw(IScreen& screen) const override;

    void Show() override;

    void Hide() override;

    SRect Rect() const override;

    std::string GetTypeName() const override;

    void Move(const SPoint& posicao) override;

private:
    SPoint m_posicao;
    SharedIText m_text;
    SFont m_font;
    TColor m_corTexto;
    TColor m_corFundo;
    mutable std::string m_textoDesenhado;
    mutable SRect m_rectDesenhado;
    std::shared_ptr<ITimer> m_timer;
};

} // namespace api
