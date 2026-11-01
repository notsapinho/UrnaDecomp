// api::CTextFieldUpdate (/home/rubio/tse/uenux2/src/api/gui/ctextfieldupdate.cpp).
// Target functions of this file:
//   3658  CTextFieldUpdate(const SPoint&, const SharedIText&, const std::chrono::milliseconds&, const SFont&, TColor,
//         TColor)  record at line 38, column 15, with the timer's lambda   (here)
//   5495 / 10917  ~CTextFieldUpdate() (base-object / deleting)   (here; out of line: the D0 calls the D2)
//   10916 Draw(IScreen&) const                                   (here)
//   10915 Show(), 10914 Hide()                                   (here)
//   10913 Rect() const     record at line 73, col 21; a thunk of fn 3889             (here)
//   10912 GetTypeName() const                                    (here)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields   (here, below Rect's line: a choice)
// The definitions follow the target's order (the uses-1 band 10912-10917 in ledger/ordinals.tsv: D0, Draw, Show, Hide,
// Rect, GetTypeName; a shared body has no place in a band); the lines but the constructor's throw's are a choice.
#include "api/gui/ctextfieldupdate.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/itimer.h"
#include "api/util/itimerscheduler.h"

namespace api {

CTextFieldUpdate::CTextFieldUpdate(const SPoint& posicao, const SharedIText& text, const std::chrono::milliseconds& intervalo,
                                   const SFont& font, TColor corTexto, TColor corFundo)
    : m_posicao(posicao)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
    , m_corFundo(corFundo)
    , m_textoDesenhado("")
    , m_timer(ITimerScheduler::GetInst().CreateTimer(intervalo,
                                                     [this]() {
                                                         Atualiza();
                                                     }))
{
    if (!m_text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDUPDATE_TEXTO_NULO, "Campo estava com o texto nulo");
    }
}

CTextFieldUpdate::~CTextFieldUpdate() = default;

void CTextFieldUpdate::Atualiza()
{
    if (m_text->GetText() != m_textoDesenhado) {
        Invalidate();
    }
}

void CTextFieldUpdate::Draw(IScreen& screen) const
{
    if (m_rectDesenhado.Width() != 1) {
        screen.FillRect(m_rectDesenhado, m_corFundo);
    }

    m_rectDesenhado = screen.DrawText(m_posicao, *m_text, m_font, m_corTexto, m_corFundo);
    m_textoDesenhado = m_text->GetText();
}

void CTextFieldUpdate::Show()
{
    m_timer->Start();
}

void CTextFieldUpdate::Hide()
{
    m_timer->Stop();
}

SRect CTextFieldUpdate::Rect() const
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    SPoint posicao = m_posicao;
    TPosition largura;
    TPosition altura;
    tela.GetFontMetrics(largura, altura, m_font, m_text->GetText());
    AlinhaPosicao(posicao, m_text->GetAlignment(), largura);

    return SRect::Normalized(posicao.x, posicao.y, posicao.x + largura, posicao.y + altura);
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
