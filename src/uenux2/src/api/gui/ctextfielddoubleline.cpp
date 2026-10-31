// api::CTextFieldDoubleLine (/home/rubio/tse/uenux2/src/api/gui/ctextfielddoubleline.cpp).
// Target functions of this file:
//   3659  CTextFieldDoubleLine(const SPoint&, const SPoint&, TPosition, const SharedIText&, const SFont&, TColor, TColor)
//         (here; its three throws are the records at lines 40, 43 and 46, column 15, so its position is fixed)
//   10926 GetTypeName() const                                                     (here; no record: placed after the ctor)
//   10928 / 10927  ~CTextFieldDoubleLine() (implicit; the target's are thunks into binaryen's merges 6022 / 6021)
//   5499  GetTextLines() const   record at line 68, col 21                         (here)
//   10931 Draw(IScreen&) const, 10929 Rect() const with CalcLineRect, record at line 133, col 21, inlined twice  (here)
//   5527  Move(const SPoint&)    one body binaryen shares with CLineField's   (here, below line 133: a choice)

#include "api/gui/ctextfielddoubleline.h"

#include "api/gui/cfixedtext.h"
#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

/**
 * Cria um campo de texto em duas linhas.
 * @param linha1, linha2 posição de cada linha; maxX não pode ser menor que o x de nenhuma
 * @param maxX posição x até onde as linhas podem ir
 * @param text texto do campo; não pode ser nulo
 * @param font fonte do texto; corTexto e corFundo, as cores do texto e do fundo
 * @throw CUeGuiError se @p text for nulo ou se maxX for menor que o x de uma linha
 */
CTextFieldDoubleLine::CTextFieldDoubleLine(const SPoint& linha1, const SPoint& linha2, TPosition maxX, const SharedIText& text, const SFont& font,
                                           TColor corTexto, TColor corFundo)
    : m_linha1(linha1)
    , m_linha2(linha2)
    , m_maxX(maxX)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
    , m_corFundo(corFundo)
{
    if (!text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDDOUBLELINE_TEXTO_NULO, "Campo estava com o texto nulo");
    }
    if (maxX < m_linha1.x) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDDOUBLELINE_MAXX_MENOR_LINHA1, "maxX menor que a posição x da linha 1");
    }
    if (maxX < m_linha2.x) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDDOUBLELINE_MAXX_MENOR_LINHA2, "maxX menor que a posição x da linha 2");
    }
}

std::string CTextFieldDoubleLine::GetTypeName() const
{
    return "CTextFieldDoubleLine";
}

// (original lines 55-60: content not recovered)
#line 61
std::tuple<std::string, std::string> CTextFieldDoubleLine::GetTextLines() const
{
    const TPosition x1 = m_linha1.x;
    const TPosition x2 = m_linha2.x;
    const TPosition maxX = m_maxX;
    std::string linha1 = m_text->GetText();
    std::string linha2 = "";
    IScreen& tela = CPolySingleton<IScreen>::instance();
    const TPosition largura1 = maxX - x1 + 1;

    if (tela.GetTextWidth(linha1, m_font) <= largura1) {
        return {linha1, linha2};
    }

    size_t espaco = linha1.rfind(' ');

    if (espaco < linha1.size()) {
        linha2 = linha1.substr(espaco + 1);
        linha1.resize(espaco);

        bool separa = true;

        while (tela.GetTextWidth(linha1, m_font) > largura1) {
            espaco = linha1.rfind(' ');

            if (espaco < linha1.size()) {
                linha2 = linha1.substr(espaco + 1) + " " + linha2;
                linha1.resize(espaco);
                separa = true;
            } else {
                if (separa) {
                    linha2 = ' ' + linha2;
                }

                linha2 = linha1.back() + linha2;
                linha1.erase(linha1.size() - 1);
                separa = false;
            }
        }
    } else {
        linha2 = linha1.back();
        linha1.erase(linha1.size() - 1);

        while (tela.GetTextWidth(linha1, m_font) > largura1) {
            linha2 = linha1.back() + linha2;
            linha1.erase(linha1.size() - 1);
        }
    }

    const TPosition largura2 = maxX - x2 + 1;

    while (!linha2.empty() && tela.GetTextWidth(linha2, m_font) > largura2) {
        linha2.erase(linha2.size() - 1);
    }

    return {linha1, linha2};
}

void CTextFieldDoubleLine::Draw(IScreen& screen) const
{
    const auto [linha1, linha2] = GetTextLines();

    screen.DrawText(m_linha1, CFixedText(linha1, m_text->GetAlignment()), m_font, m_corTexto, m_corFundo);

    if (!linha2.empty()) {
        screen.DrawText(m_linha2, CFixedText(linha2, m_text->GetAlignment()), m_font, m_corTexto, m_corFundo);
    }
}


SRect CTextFieldDoubleLine::CalcLineRect(const std::string& linha, SPoint posicao) const
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    TPosition largura;
    TPosition altura;
    tela.GetFontMetrics(largura, altura, m_font, linha);
    AlinhaPosicao(posicao, m_text->GetAlignment(), largura);

    return SRect::Normalized(posicao.x, posicao.y, posicao.x + largura, posicao.y + altura);
}

SRect CTextFieldDoubleLine::Rect() const
{
    const auto [linha1, linha2] = GetTextLines();
    SRect rect = CalcLineRect(linha1, m_linha1);

    if (!linha2.empty()) {
        rect = rect.Union(CalcLineRect(linha2, m_linha2));
    }

    return rect;
}

void CTextFieldDoubleLine::Move(const SPoint& posicao)
{
    if (posicao.x == m_linha1.x && posicao.y == m_linha1.y) {
        return;
    }

    const TPosition dx = posicao.x - m_linha1.x;
    const TPosition dy = posicao.y - m_linha1.y;

    m_linha2.x += dx;
    m_linha2.y += dy;
    m_linha1 = posicao;

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

} // namespace api
