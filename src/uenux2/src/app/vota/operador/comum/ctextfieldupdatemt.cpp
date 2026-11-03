// api::CTextFieldUpdateMT (/home/rubio/tse/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.cpp; no record
// names the file: the path is chosen, see src/units/51-uenux2-ctextfieldupdatemt.mk).
// Target functions of this file:
//   (no index) CTextFieldUpdateMT(const SPoint&, const SharedIText&, const std::chrono::milliseconds&)
//         inlined by binaryen into fn 652, with the timer's lambda   (here; the lambda's __func members are
//         fns 10544 to 10540, operator() 10542)
//   (no index) Atualiza(), inlined by binaryen into the lambda's operator() (fn 10542)   (here)
//   5411 / 10549  ~CTextFieldUpdateMT() (base-object / deleting)   (here; out of line: the D0 calls the D2)
//   10548 Draw(IScreenMT&) const                                   (here)
//   10546 Show(), 10545 Hide()                                     (here)
//   11051 IFormField<IScreenMT>::GetTypeName() const               (slot 7, inline in api/gui/iformfield.h)
// No record falls in this file, so every line is a choice; the definitions follow the target's order (the uses-1 band
// 10545-10549 of ledger/ordinals.tsv runs in reverse link order: D0, Draw, Show, Hide), the constructor first and
// Atualiza after the destructor, as api/gui/ctextfieldupdate.cpp has them.

#include "app/vota/operador/comum/ctextfieldupdatemt.h"

#include <stdexcept>

#include "api/gui/cfixedtext.h"
#include "api/gui/iform.h"
#include "api/gui/iscreenmt.h"
#include "api/util/itimer.h"
#include "api/util/itimerscheduler.h"

namespace api {

CTextFieldUpdateMT::CTextFieldUpdateMT(const SPoint& posicao, const SharedIText& text,
                                       const std::chrono::milliseconds& intervalo)
    : m_posicao(posicao)
    , m_text(text)
    , m_textoDesenhado("")
    , m_timer(ITimerScheduler::GetInst().CreateTimer(intervalo,
                                                     [this]() {
                                                         Atualiza();
                                                     }))
{
    if (!m_text) {
        throw std::invalid_argument("CTextFieldUpdate - campo estava com o texto nulo");
    }
}

CTextFieldUpdateMT::~CTextFieldUpdateMT() = default;

void CTextFieldUpdateMT::Atualiza()
{
    if (m_text->GetText() != m_textoDesenhado) {
        Invalidate();
    }
}

void CTextFieldUpdateMT::Draw(IScreenMT& screen) const
{
    if (m_textoDesenhado.size() > m_text->GetText().size()) {
        screen.ShowText(m_posicao, CFixedText(std::string(m_textoDesenhado.size(), ' ')));
    }
    screen.ShowText(m_posicao, *m_text);
    m_textoDesenhado = m_text->GetText();
}

void CTextFieldUpdateMT::Show()
{
    m_timer->Start();
}

void CTextFieldUpdateMT::Hide()
{
    m_timer->Stop();
}

} // namespace api
