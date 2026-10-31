// api::CTextFieldBlinking (/home/rubio/tse/uenux2/src/api/gui/ctextfieldblinking.cpp, the file the records of the
// constructor and of Rect name). This comment is the reconstruction's. Target functions of this file:
//   the constructor   records at lines 39 and 42, column 15; binaryen inlined it into fn 1265; not reconstructed
//   10946 Draw(IScreen&) const                                                                 (here)
//   10945 Show(), 10944 Hide()                                                                 (here)
//   10943 Rect() const   record at line 70, column 21; calls fn 3889, not named yet            (pending)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields                 (here)
//   10942 / 10941  the implicit destructors, emitted here with the vtable: Draw is the key function
//   10940 GetTypeName() const: through fn 3891, which has no name yet                          (pending)
// Draw, Show and Hide follow the target's order (the uses-1 band 10940-10946 of ledger/ordinals.tsv: Draw, Show, Hide,
// Rect, the destructors, GetTypeName); no record falls in them, so their lines are a choice. Move shares its body, so
// the band does not place it: below Rect's line is a choice. The pending members are in the unit's -pending.cpp.

#include "api/gui/ctextfieldblinking.h"

#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/util/itimer.h"

namespace api {

// (original lines 22-52: content not recovered)
#line 53
void CTextFieldBlinking::Draw(IScreen& screen) const
{
    screen.DrawText(m_posicao, *m_text, m_font, m_aceso ? m_corTexto : m_corPisca, m_corFundo);
}

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
