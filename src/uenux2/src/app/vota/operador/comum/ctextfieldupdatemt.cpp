// api::CTextFieldUpdateMT (/home/rubio/tse/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.cpp; no record
// names the file: the path is chosen, see src/units/51-uenux2-ctextfieldupdatemt.mk).
// Target functions of this file:
//   (no index) CTextFieldUpdateMT(const SPoint&, const SharedIText&, const std::chrono::milliseconds&)
//         inlined into fn 652; not reconstructed. It calls ITimerScheduler::GetInst (fn 1259), which unit 101
//         holds
//   5411 / 10549  ~CTextFieldUpdateMT() (base-object / deleting)   (here; out of line: the D0 calls the D2)
//   10548 Draw(IScreenMT&) const                                   (here)
//   10546 Show(), 10545 Hide()                                     (here)
//   11051 IFormField<IScreenMT>::GetTypeName() const               (slot 7, inline in api/gui/iformfield.h)
// No record falls in this file, so every line is a choice; the definitions follow the target's order (the uses-1 band
// 10545-10549 of ledger/ordinals.tsv runs in reverse link order: D0, Draw, Show, Hide).

#include "app/vota/operador/comum/ctextfieldupdatemt.h"

#include "api/gui/cfixedtext.h"
#include "api/gui/iscreenmt.h"
#include "api/util/itimer.h"

namespace api {

CTextFieldUpdateMT::~CTextFieldUpdateMT() = default;

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
