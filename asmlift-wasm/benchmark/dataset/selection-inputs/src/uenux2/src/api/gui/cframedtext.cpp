// Reconstruction's note, not TSE's text. The file's records are the constructor's, line 28, and MaskText's, line 66.
// The constructor's and MaskText's other lines, and DrawChar, FillCell, Rect, Move and DrawFrame, which have no record,
// their being in this file and their lines, are chosen (src/units/92-uenux2-iinputfield.mk).
#include <algorithm>
#include <string>

#include "api/gui/cfixedtext.h"
#include "api/gui/cframedtext.h"
#include "api/gui/eueguierror.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

// (original lines 15-21: content not recovered)
#line 22
CFramedText::CFramedText(size_t length, const SPoint& position, const SFont& font, ETextAlignment alignment)
    : m_length(length)
    , m_position(position)
    , m_font(font)
    , m_alignment(alignment)
{
    IScreen& monitor = CPolySingleton<IScreen>::instance();
    monitor.GetFontMetrics(m_largura, m_altura, m_font);

    m_largura += 2 * Espaco();

    const TPosition espacoVertical = m_font.size / 10;
    m_altura += 2 * (espacoVertical > 0 ? espacoVertical : 1);

    const size_t largura = (m_length - 1) * Espaco() + m_length * m_largura;

    switch (m_alignment) {
        case ALINHAMENTO_DIREITA:
            m_position.x -= largura;
            break;
        case ALINHAMENTO_CENTRO:
            m_position.x -= largura / 2;
            break;
        default:
            break;
    }
}

void CFramedText::DrawChar(size_t index, char caractere, IScreen& screen) const
{
    const CFixedText texto(std::string(1, caractere), ALINHAMENTO_CENTRO);
    SRect rect = CellRect(index);
    rect.Left(rect.left + Espaco());
    rect.Right(rect.right - Espaco());
    rect.Top(rect.top + EspacoVertical());
    rect.Bottom(rect.bottom - EspacoVertical());
    const int metade = (rect.right - rect.left) / 2;
    const SPoint centro{static_cast<TPosition>(rect.left + metade), static_cast<TPosition>(rect.top + 1)};
    screen.DrawText(centro, texto, m_font, static_cast<TColor>(2), static_cast<TColor>(1));
}

void CFramedText::MaskText(IScreen& screen, const std::string& text) const
{
    if (text.size() > m_length) {
        throw CUeGuiError(EUE_GUI_FRAMEDTEXT_TEXTO_GRANDE_DEMAIS, "Texto [" + text + "] eh grande demais");
    }

    std::string texto(text);
    texto.append(m_length - text.size(), ' ');

    for (size_t i = 0; i < texto.size(); ++i) {
        const char caractere = texto[i];
        if (caractere == ' ') {
            FillCell(i, static_cast<TColor>(1), screen);
            DrawFrame(i, static_cast<TColor>(2), screen);
        } else {
            DrawChar(i, caractere, screen);
            DrawFrame(i, static_cast<TColor>(3), screen);
        }
    }
}

void CFramedText::FillCell(size_t index, TColor color, IScreen& screen) const
{
    screen.FillRect(CellRect(index), color);
}

SRect CFramedText::Rect() const
{
    const TPosition x1 = m_position.x;
    const TPosition y1 = m_position.y;
    const TPosition x2 = x1 + Largura();
    const TPosition y2 = y1 + m_altura;
    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
}

void CFramedText::Move(const SPoint& position)
{
    m_position = position;
}

void CFramedText::SetLength(size_t length)
{
    if (length == m_length) {
        return;
    }

    m_length = length;

    const size_t largura = (m_length - 1) * Espaco() + m_length * m_largura;

    switch (m_alignment) {
        case ALINHAMENTO_DIREITA:
            m_position.x -= largura;
            break;
        case ALINHAMENTO_CENTRO:
            m_position.x -= largura / 2;
            break;
        default:
            break;
    }
}

void CFramedText::DrawFrame(size_t index, TColor color, IScreen& screen) const
{
    screen.DrawRect(CellRect(index), color, 1);
}

} // namespace api
