// api::CTextFieldMultiLine (/home/rubio/tse/uenux2/src/api/gui/ctextfieldmultiline.cpp).
// Target functions of this file:
//   5498  CTextFieldMultiLine(const SRect&, const SharedIText&, const SFont&, TColor, TColor)   (here; its throw is
//         the record at line 71, column 15, so the ctor's position in this file is fixed)
//   10921 GetTypeName() const                                       (in the class: ctextfieldmultiline.h says why)
//   10923 / 10922  ~CTextFieldMultiLine() (complete / deleting; implicit, emitted with the vtable)
//   5497  GetTextLines() const   record at line 116, col 21: CPolySingleton<IScreen>::instance()  (here)
//   10925 Draw(IScreen&) const                                                              (here)
//   10924 Rect() const                                                                      (here)
//   2783  Move(const SPoint&)    one body binaryen shares with CFillField/CRectField/CTextRectField (here)
// src/units/14-uenux2-ctextfieldmultiline.mk says what each member rests on.

#include "api/gui/ctextfieldmultiline.h"

#include <algorithm>
#include <cmath>
#include <sstream>

#include "api/gui/cfixedtext.h"
#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
namespace api {
namespace {
/**
 * Divisor da altura da fonte que dá o espaço entre duas linhas: cada linha
 * ocupa a altura da fonte mais um sexto dela, arredondado para cima.
 */
constexpr double DIVISOR_ESPACO_ENTRE_LINHAS = 6.0;
} // namespace
/**
 * Cria um campo de texto com várias linhas.
 *
 * O texto é obtido de @p text a cada desenho e quebrado em linhas que cabem na
 * largura de @p rect, sempre num espaço entre palavras quando há um; uma
 * palavra maior que a largura do retângulo é quebrada no último caractere que
 * cabe. As linhas são desenhadas de cima para baixo a partir do topo do
 * retângulo, alinhadas horizontalmente como o texto pedir (à esquerda, ao
 * centro ou à direita), até a última que cabe inteira na altura do retângulo;
 * as demais são descartadas.
 *
 * A área efetivamente ocupada pelo texto (a união dos retângulos das linhas
 * desenhadas) é guardada no desenho, para que o próximo desenho apague apenas
 * ela com a cor de fundo antes de escrever o texto novo, e é o que Rect()
 * devolve depois do primeiro desenho. Antes dele, Rect() calcula a área que o
 * texto ocuparia.
 *
 * O campo não guarda o texto quebrado: um texto dinâmico (CDataText,
 * CDataTextFmt) é lido de novo a cada desenho.
 *
 * As cores são as da paleta da tela (TColor).
 *
 * @param rect retângulo onde o texto é desenhado
 * @param text texto do campo; não pode ser nulo
 * @param font fonte do texto
 * @param corTexto cor do texto
 * @param corFundo cor do fundo, usada também para apagar o texto anterior
 *
 * @throw CUeGuiError se @p text for nulo
 */
CTextFieldMultiLine::CTextFieldMultiLine(const SRect& rect, const SharedIText& text, const SFont& font, TColor corTexto, TColor corFundo)
    : m_rect(rect)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
    , m_corFundo(corFundo)
    , m_alturaLinha(static_cast<TPosition>(font.size + std::ceil(font.size / DIVISOR_ESPACO_ENTRE_LINHAS)))
{
    if (!text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDMULTILINE_TEXTO_NULO, "Campo estava com o texto nulo");
    }
}

// (original lines 75-79: content not recovered)
#line 80
void CTextFieldMultiLine::Move(const SPoint& posicao)
{
    if (posicao.x == m_rect.left && posicao.y == m_rect.top) {
        return;
    }

    m_rect.Move(posicao);

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

// (original lines 94-110: content not recovered)
#line 111
std::vector<std::string> CTextFieldMultiLine::GetTextLines() const
{
    const int largura = m_rect.Width();
    const std::string texto = m_text->GetText();
    std::vector<std::string> linhas;
    IScreen& tela = CPolySingleton<IScreen>::instance();
    std::istringstream stream(texto);
    std::string linha;
    const auto larguraPrefixo = [&](size_t tamanho) { return tela.GetTextWidth(linha.substr(0, tamanho), m_font); };

    while (std::getline(stream, linha)) {
        if (linha.empty()) {
            linhas.push_back(linha);
            continue;
        }

        while (!linha.empty()) {
            size_t corte = std::string::npos;

            if (tela.GetTextWidth(linha, m_font) > largura) {
                size_t espaco = linha.find(' ');

                while (espaco != std::string::npos && larguraPrefixo(espaco) <= largura) {
                    corte = espaco;
                    espaco = linha.find(' ', espaco + 1);
                }

                if (corte == std::string::npos) {
                    size_t tamanho = 1;

                    while (tamanho < linha.size() && larguraPrefixo(tamanho) <= largura) {
                        ++tamanho;
                    }

                    if (tamanho < linha.size()) {
                        corte = tamanho - 1;
                    }
                }
            }

            linhas.push_back(linha.substr(0, corte));

            if (corte == std::string::npos) {
                linha.clear();
            } else if (corte == 0) {
                return linhas;
            } else if (linha[corte] == ' ') {
                linha.erase(0, corte + 1);
            } else {
                linha.erase(0, corte);
            }
        }
    }

    return linhas;
}

void CTextFieldMultiLine::Draw(IScreen& screen) const
{
    const std::vector<std::string> linhas = GetTextLines();
    TPosition y = m_rect.top;

    if (m_desenhado) {
        screen.FillRect(m_rectDesenhado, m_corFundo);
    }

    m_rectDesenhado = Rect();

    for (const std::string& linha : linhas) {
        if (m_rect.bottom < m_alturaLinha + y) {
            break;
        }

        const int larguraLinha = screen.GetTextWidth(linha, m_font);
        TPosition x;

        switch (m_text->GetAlignment()) {
            case ALINHAMENTO_DIREITA:
                x = m_rect.right - larguraLinha;
                break;
            case ALINHAMENTO_CENTRO:
                x = m_rect.left + (m_rect.right - (larguraLinha + m_rect.left)) / 2;
                break;
            default:
                x = m_rect.left;
                break;
        }

        const SRect desenhado = screen.DrawText(SPoint{x, y}, CFixedText(linha), m_font, m_corTexto, m_corFundo);
        y += m_alturaLinha;
        m_rectDesenhado = m_rectDesenhado.Union(desenhado);
    }

    m_desenhado = true;
}

SRect CTextFieldMultiLine::Rect() const
{
    if (m_rectDesenhado.left != 0 || m_rectDesenhado.top != 0 || m_rectDesenhado.right != 0 || m_rectDesenhado.bottom != 0) {
        return m_rectDesenhado;
    }

    const std::vector<std::string> linhas = GetTextLines();
    const TPosition y = m_rect.top + m_alturaLinha * linhas.size();

    return SRect::Normalized(m_rect.left, m_rect.top, m_rect.right, std::min(m_rect.bottom, y));
}

} // namespace api
