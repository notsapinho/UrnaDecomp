// api::CTextField (/home/rubio/tse/uenux2/src/api/gui/ctextfield.cpp). Target functions of this file:
//   1918  CTextField(const SPoint&, const SharedIText&, const SFont&, TColor, TColor)  (here; record at line 30, col 15)
//   10947 GetTypeName() const                                   (here)
//   10950 / 10948  ~CTextField() (complete / deleting; implicit, emitted with the vtable)
//   10952 Draw(IScreen&) const                                  (here)
//   10951 Rect() const  record at line 55, col 21; a thunk of fn 3889, its body and two other classes'   (here)
//   2241  Move(const SPoint&)  one body binaryen shares with four other fields   (here, below Rect's line: a choice)

#include "api/gui/ctextfield.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

/**
 * Cria um campo de texto de uma linha em @p posicao; o texto é lido de @p text a cada desenho.
 * @throw CUeGuiError se @p text for nulo
 */
CTextField::CTextField(const SPoint& posicao, const SharedIText& text, const SFont& font, TColor corTexto, TColor corFundo)
    : m_posicao(posicao)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
    , m_corFundo(corFundo)
{
    if (!m_text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELD_TEXTO_NULO, "Campo estava com o texto nulo");
    }
}

std::string CTextField::GetTypeName() const
{
    return "CTextField";
}

void CTextField::Draw(IScreen& screen) const
{
    if (m_apagar) {
        screen.FillRect(m_rectDesenhado, m_corFundo);
    }

    m_rectDesenhado = screen.DrawText(m_posicao, *m_text, m_font, m_corTexto, m_corFundo);
    m_apagar = false;
}

// (original lines 49-52: content not recovered)
#line 53
SRect CTextField::Rect() const
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    SPoint posicao = m_posicao;
    TPosition largura;
    TPosition altura;
    tela.GetFontMetrics(largura, altura, m_font, m_text->GetText());
    AlinhaPosicao(posicao, m_text->GetAlignment(), largura);

    return SRect::Normalized(posicao.x, posicao.y, posicao.x + largura, posicao.y + altura);
}

void CTextField::Move(const SPoint& posicao)
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
