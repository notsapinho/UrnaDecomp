// api::CTextRectField (/home/rubio/tse/uenux2/src/api/gui/ctextrectfield.cpp, the file the records of the constructor
// and of Rect name). This comment is the reconstruction's. Target functions of this file:
//   the constructor   record at line 51, column 15; binaryen inlined it into fn 5546
//   10906 Draw(IScreen&) const                                                         (here)
//   10905 Rect() const   record at line 71, column 21; calls fn 512, not named yet     (pending)
//   10904 / 10903  the implicit destructors, emitted here with the vtable: Draw is the key function
//   10902 GetTypeName() const   in the class
//   2783  Move(const SPoint&)   calls fn 1915, which has no name                       (pending)
// The lines around the constructor's throw and Draw's are a choice; Draw sits above Rect's line, in the band's order
// (uses 1, 10902-10906). The pending members are in src/units/90-uenux2-api-gui-pending.cpp.

#include "api/gui/ctextrectfield.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iscreen.h"

namespace api {

// (original lines 19-42: content not recovered)
#line 43
CTextRectField::CTextRectField(const SRect& rect, TColor corFundo, const SharedIText& text, const SFont& font, TColor corTexto)
    : m_rect(rect)
    , m_corFundo(corFundo)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
{
    if (!m_text) {
        throw CUeGuiError(EUE_GUI_TEXTRECTFIELD_TEXTO_NULO, "Campo estava com o texto nulo");
    }
}

void CTextRectField::Draw(IScreen& screen) const
{
    if (m_rectDesenhado.Width() != 1) {
        screen.FillRect(m_rectDesenhado, m_preencher ? m_corFundo : static_cast<TColor>(1));
    }

    if (m_preencher) {
        m_rectDesenhado = screen.DrawText(m_rect, *m_text, m_font, m_corTexto, m_corFundo);
    } else {
        m_rectDesenhado = screen.DrawText(m_rect, *m_text, m_font, m_corTexto, static_cast<TColor>(0));
    }
}





} // namespace api
