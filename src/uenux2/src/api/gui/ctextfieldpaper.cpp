// api::CTextFieldPaper (/home/rubio/tse/uenux2/src/api/gui/ctextfieldpaper.cpp).
// Target functions of this file:
//   2771  CTextFieldPaper(const SharedIText&, IPaper::EStyle)   (here; its throw is the record at line 23, column 15)
//   10920 Draw(IPaper&) const        (here; the class's only virtual member defined out of line, so the vtable is here)
//   10919 / 10918  ~CTextFieldPaper() (complete / deleting; implicit, emitted with the vtable)
//   11014 IFormField<IPaper>::GetTypeName() const                (slot 7, inline in api/gui/iformfield.h)

#include "api/gui/ctextfieldpaper.h"

#include "api/gui/eueguierror.h"

namespace api {

/**
 * Cria um campo que imprime o texto de @p text no estilo @p estilo.
 * @throw CUeGuiError se @p text for nulo
 */
CTextFieldPaper::CTextFieldPaper(const SharedIText& text, IPaper::EStyle estilo)
    : m_text(text)
    , m_estilo(estilo)
{
    if (!m_text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDPAPER_TEXTO_NULO, "Campo estava com o texto nulo");
    }
}

void CTextFieldPaper::Draw(IPaper& paper) const
{
    paper.PrintText(*m_text, m_estilo);
}

} // namespace api
