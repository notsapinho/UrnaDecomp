// api::CTextFieldMT (/home/rubio/tse/uenux2/src/api/gui/ctextfieldmt.cpp).
// Target functions of this file:
//   1262  CTextFieldMT(const SPoint&, const SharedIText&)   (here; its throw is the record at line 25, column 15)
//   10933 / 10932  ~CTextFieldMT() (complete / deleting; implicit, emitted with the vtable)
//   10934 Draw(IScreenMT&) const                            (pending)
//   11051 IFormField<IScreenMT>::GetTypeName() const        (slot 7, inline in api/gui/iformfield.h)
// Draw is defined in src/units/30-uenux2-ctextfieldmt-pending.cpp until it is reconstructed.

#include "api/gui/ctextfieldmt.h"

#include "api/gui/eueguierror.h"

namespace api {

/**
 * Cria um campo de texto na posição @p posicao da tela MT.
 *
 * @throw CUeGuiError se @p text for nulo
 */
CTextFieldMT::CTextFieldMT(const SPoint& posicao, const SharedIText& text)
    : m_posicao(posicao)
    , m_text(text)
{
    if (!m_text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDMT_TEXTO_NULO, "Campo estava com o texto nulo");
    }
}

} // namespace api
