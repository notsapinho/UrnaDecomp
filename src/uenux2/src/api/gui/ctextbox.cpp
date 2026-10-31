// api::CTextBox (/home/rubio/tse/uenux2/src/api/gui/ctextbox.cpp, the file the class's records name).
// Target functions of this file:
//   10958 Draw(IScreen&) const   record at line 69, column 19   (here)
//   10957 Move(const SPoint&)    record at line 90, column 15   (here)
//   10956 Rect() const           record at line 110, column 9   (here)
// The constructor (record at line 41, column 15, code 4961) has no target function: binaryen inlined it into fn 11805.
// The lines around the throws are a choice. Draw is the key function, so this object emits the vtable, the destructors
// and GetTypeName.

#include "api/gui/ctextbox.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

// (original lines 19-28: content not recovered)
#line 29
CTextBox::CTextBox(const std::string& texto, ETextStatus status, SPoint posicao, TFontSize tamanhoFonte,
                   ETextAlignment alinhamento, SPoint tamanho, TColor corTexto, TColor corFundo)
    : m_texto(texto, alinhamento)
    , m_status(status)
    , m_posicao(posicao)
    , m_tamanhoFonte(tamanhoFonte)
    , m_corTexto(corTexto)
    , m_corFundo(corFundo)
    , m_altura(tamanho.y)
    , m_largura(tamanho.x)
{
    if (m_posicao.x < 3 || m_posicao.y < 1) {
        throw CUeGuiError(EUE_GUI_TEXTBOX_POSICAO_INICIAL_INVALIDA, "A posição da caixa não pode ter x < 3 ou y < 1.");
    }
}

void CTextBox::Draw(IScreen& screen) const
{
    const SRect rect = Rect();
    const SPoint posicao{static_cast<TPosition>(rect.left + rect.Width() / 2), static_cast<TPosition>(rect.top + 4)};
    const CFixedText texto(m_texto.GetText(), ALINHAMENTO_CENTRO);

    screen.Clear(rect, static_cast<TColor>(1));
    switch (m_status) {
        case TEXTSTATUS_CONTORNO:
            screen.SetColors(m_corFundo, m_corTexto);
            screen.DrawRect(rect, m_corFundo, 1);
            screen.DrawText(posicao, texto, SFont{m_tamanhoFonte, 0}, m_corFundo, static_cast<TColor>(0));
            break;
        case TEXTSTATUS_DESTAQUE:
            screen.FillRect(rect, static_cast<TColor>(4));
            screen.SetColors(m_corFundo, static_cast<TColor>(4));
            screen.DrawText(posicao, texto, SFont{m_tamanhoFonte, 0}, m_corTexto, static_cast<TColor>(0));
            break;
        case TEXTSTATUS_PREENCHIDO:
            screen.SetColors(m_corTexto, m_corFundo);
            screen.FillRect(rect, m_corFundo);
            screen.DrawText(posicao, texto, SFont{m_tamanhoFonte, 0}, m_corTexto, static_cast<TColor>(0));
            break;
        default:
            throw CUeGuiError(EUE_GUI_TEXTBOX_STATUS_INDEFINIDO, "Status indefinido");
    }

    screen.SetColors(m_corFundo, m_corTexto);
}

// (original lines 75-80: content not recovered)
#line 81
void CTextBox::Move(const SPoint& posicao)
{
    if (posicao.x == m_posicao.x && posicao.y == m_posicao.y) {
        return;
    }

    m_posicao = posicao;

    if (m_posicao.x < 3 || m_posicao.y < 1) {
        throw CUeGuiError(EUE_GUI_TEXTBOX_POSICAO_INVALIDA, "A posição da caixa não pode ter x < 3 ou y < 1.");
    }

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}


SRect CTextBox::Rect() const
{
    SRect rect;

    if (m_largura != 0 && m_altura != 0) {
        rect = SRect::Normalized(m_posicao.x, m_posicao.y, m_posicao.x + m_largura, m_posicao.y + m_altura);
    } else {
        TPosition largura;
        TPosition altura;

        CPolySingleton<IScreen>::instance().GetFontMetrics(largura, altura, SFont{m_tamanhoFonte, 0}, m_texto.GetText());
        rect = SRect::Normalized(m_posicao.x, m_posicao.y, m_posicao.x + largura + 20, m_posicao.y + altura + 8);
    }

    switch (m_texto.GetAlignment()) {
        case ALINHAMENTO_DIREITA:
            rect.MoveX(rect.left - rect.Width());
            break;
        case ALINHAMENTO_CENTRO:
            rect.MoveX(rect.left - rect.Width() / 2);
            break;
        default:
            break;
    }

    return rect;
}

} // namespace api
