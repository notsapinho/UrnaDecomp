// api::CTextFieldBlinking (/home/rubio/tse/uenux2/src/api/gui/ctextfieldblinking.cpp, the file the records of the
// constructor and of Rect name). This comment is the reconstruction's. Target functions of this file:
//   the constructor   records at lines 39 and 42, column 15; binaryen inlined it into fn 1265, with its timer's lambda (here)
//   10946 Draw(IScreen&) const                                                                 (here)
//   10945 Show(), 10944 Hide()                                                                 (here)
//   10943 Rect() const   record at line 70, column 21; a thunk of fn 3889                      (here)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields                 (here)
//   10942 / 10941  the implicit destructors, emitted here with the vtable: Draw is the key function
//   10940 GetTypeName() const: in the class, a thunk of fn 3891, a merge of three 18-character names
// Draw, Show and Hide follow the target's order (the uses-1 band 10940-10946 of ledger/ordinals.tsv: Draw, Show, Hide,
// Rect, the destructors, GetTypeName); no record falls in them, so their lines are a choice. Move shares its body, so
// the band does not place it: below Rect's line is a choice.

#include "api/gui/ctextfieldblinking.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/itimer.h"
#include "api/util/itimerscheduler.h"

namespace api {

CTextFieldBlinking::CTextFieldBlinking(const SPoint& posicao, const SharedIText& text, const SFont& font, TColor corTexto,
                                       TColor corPisca, TColor corFundo)
    : m_posicao(posicao)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
    , m_corPisca(corPisca)
    , m_corFundo(corFundo)
    , m_timer(ITimerScheduler::GetInst().CreateTimer(std::chrono::milliseconds(500), [this]() {
          m_aceso = !m_aceso;
          Invalidate();
      }))
{
    if (!m_text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDBLINKING_TEXTO_NULO, "Campo estava com o texto nulo");
    }
    if (m_corTexto == m_corPisca) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDBLINKING_CORES_IGUAIS, "As cores estavam iguais");
    }
}

// (original lines 46-52: content not recovered)
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

SRect CTextFieldBlinking::Rect() const
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    SPoint posicao = m_posicao;
    TPosition largura;
    TPosition altura;
    tela.GetFontMetrics(largura, altura, m_font, m_text->GetText());
    AlinhaPosicao(posicao, m_text->GetAlignment(), largura);

    return SRect::Normalized(posicao.x, posicao.y, posicao.x + largura, posicao.y + altura);
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
