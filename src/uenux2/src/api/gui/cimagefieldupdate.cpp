// api::CImageFieldUpdate (/home/rubio/tse/uenux2/src/api/gui/cimagefieldupdate.cpp, the file the records of the
// constructor and of Rect name). This comment is the reconstruction's. Target functions of this file:
//   the constructor   record at line 32, column 15; binaryen inlined it into fn 3059; not reconstructed
//   11090 Draw(IScreen&) const                                                                 (here)
//   11089 Show(), 11088 Hide()                                                                 (here)
//   11087 Rect() const   record at line 80, column 12; calls fn 512, not named yet             (pending)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields                 (here)
// The destructors and GetTypeName are in the class; Draw, the key function, makes this object emit them with the vtable.
// Draw, Show and Hide follow the target's order (the uses-1 band 11085-11090 of ledger/ordinals.tsv: Draw, Show, Hide,
// Rect, the deleting destructor, GetTypeName); no record falls in them, so their lines are a choice. Move shares its
// body, so the band does not place it: below Rect's line is a choice. Rect is in 43-uenux2-cimagefieldupdate-pending.cpp.

#include "api/gui/cimagefieldupdate.h"

#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/util/itimer.h"

namespace api {

// (original lines 21-57: content not recovered)
#line 58
void CImageFieldUpdate::Draw(IScreen& screen) const
{
    if (m_tamanho == nullptr) {
        screen.DrawImage(m_posicao, *m_imagem, m_ancora);
    } else {
        screen.DrawImage(m_posicao, *m_imagem, *m_tamanho, m_ancora);
    }
}


void CImageFieldUpdate::Show()
{
    m_timer->Start();
}

void CImageFieldUpdate::Hide()
{
    m_timer->Stop();
}









void CImageFieldUpdate::Move(const SPoint& posicao)
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
