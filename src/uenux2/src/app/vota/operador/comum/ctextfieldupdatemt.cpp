// api::CTextFieldUpdateMT (/home/rubio/tse/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.cpp; no record
// names the file: the path is chosen, see src/units/51-uenux2-ctextfieldupdatemt.mk).
// Target functions of this file:
//   (no index) CTextFieldUpdateMT(const SPoint&, const SharedIText&, const std::chrono::milliseconds&)
//         inlined into fn 652; not reconstructed: it calls ITimerScheduler::GetInst (fn 1259), which has no body of
//         ours
//   5411 / 10549  ~CTextFieldUpdateMT() (base-object / deleting)   (here; out of line: the D0 calls the D2)
//   10548 Draw(IScreenMT&) const                                   (pending)
//   10546 Show(), 10545 Hide()                                     (here)
//   11051 IFormField<IScreenMT>::GetTypeName() const               (slot 7, inline in api/gui/iformfield.h)
// No record falls in this file, so every line is a choice; the definitions follow the target's order (the uses-1 band
// 10545-10549 of ledger/ordinals.tsv runs in reverse link order: D0, Draw, Show, Hide). Draw is defined in
// src/units/51-uenux2-ctextfieldupdatemt-pending.cpp until it is reconstructed.

#include "app/vota/operador/comum/ctextfieldupdatemt.h"

#include "api/util/itimer.h"

namespace api {

CTextFieldUpdateMT::~CTextFieldUpdateMT() = default;

void CTextFieldUpdateMT::Show()
{
    m_timer->Start();
}

void CTextFieldUpdateMT::Hide()
{
    m_timer->Stop();
}

} // namespace api
