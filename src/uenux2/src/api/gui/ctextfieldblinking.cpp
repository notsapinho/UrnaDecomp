// api::CTextFieldBlinking (/home/rubio/tse/uenux2/src/api/gui/ctextfieldblinking.cpp, the file the records of the
// constructor and of Rect name). This comment is the reconstruction's. Target functions of this file:
//   the constructor   records at lines 39 and 42, column 15; binaryen inlined it into fn 1265; not reconstructed
//   10946 Draw(IScreen&) const                                                                 (pending)
//   10945 Show(), 10944 Hide()                                                                 (here)
//   10943 Rect() const   record at line 70, column 21; calls fn 3889, not named yet            (pending)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields                 (here)
//   10942 / 10941  the implicit destructors, emitted with the vtable in the pending object, whose Draw is the key
//   function; 10940 GetTypeName() const: through fn 3891, which has no name yet                (pending)
// Show and Hide follow the target's order (the uses-1 band 10940-10946 of ledger/ordinals.tsv: Draw, Show, Hide, Rect,
// the destructors, GetTypeName); no record falls in them, so their lines are a choice. Move shares its body, so the band
// does not place it: below Rect's line is a choice. The pending members are defined in
// src/units/44-uenux2-ctextfieldblinking-pending.cpp.

#include "api/gui/ctextfieldblinking.h"

#include "api/gui/iform.h"
#include "api/util/itimer.h"

namespace api {

// (original lines 22-57: content not recovered)
#line 58
void CTextFieldBlinking::Show()
{
    m_timer->Start();
}

void CTextFieldBlinking::Hide()
{
    m_timer->Stop();
}









void CTextFieldBlinking::Move(const SPoint& posicao)
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

} // namespace api
