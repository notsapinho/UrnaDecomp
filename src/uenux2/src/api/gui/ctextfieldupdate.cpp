// api::CTextFieldUpdate (/home/rubio/tse/uenux2/src/api/gui/ctextfieldupdate.cpp).
// Target functions of this file:
//   3658  CTextFieldUpdate(const SPoint&, const SharedIText&, const std::chrono::milliseconds&, const SFont&, TColor,
//         TColor)  record at line 38, column 15 (the null-text throw); not reconstructed: it calls
//         ITimerScheduler::GetInst (fn 1259), which has no body of ours yet, so line 38 stays free for it
//   5495 / 10917  ~CTextFieldUpdate() (base-object / deleting)   (here; out of line: the D0 calls the D2)
//   10916 Draw(IScreen&) const                                   (pending)
//   10915 Show(), 10914 Hide()                                   (here)
//   10913 Rect() const     record at line 73, col 21; calls fn 3889, not named yet   (pending)
//   10912 GetTypeName() const                                    (here)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields   (here, below Rect's line: a choice)
// The definitions follow the target's order (the uses-1 band 10912-10917 in ledger/ordinals.tsv: D0, Draw, Show, Hide,
// Rect, GetTypeName; a shared body has no place in a band); no record falls in the members written here, so their lines
// are a choice. The pending members are defined in src/units/42-uenux2-ctextfieldupdate-pending.cpp.

#include "api/gui/ctextfieldupdate.h"

#include "api/gui/iform.h"
#include "api/util/itimer.h"

namespace api {

// (original lines 23-34: content not recovered)
#line 35
// <stubs>
// f3658 · 303 B · unmatched · name unknown
// ? f3658(i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 40-41: content not recovered)
#line 42
CTextFieldUpdate::~CTextFieldUpdate() = default;

// (original lines 44-59: content not recovered)
#line 60
void CTextFieldUpdate::Show()
{
    m_timer->Start();
}

void CTextFieldUpdate::Hide()
{
    m_timer->Stop();
}










void CTextFieldUpdate::Move(const SPoint& posicao)
{
    if (posicao.x == m_posicao.x && posicao.y == m_posicao.y) {
        return;
    }

    m_posicao = posicao;

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

std::string CTextFieldUpdate::GetTypeName() const
{
    return "CTextFieldUpdate";
}

} // namespace api
