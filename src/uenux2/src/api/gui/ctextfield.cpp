// api::CTextField (/home/rubio/tse/uenux2/src/api/gui/ctextfield.cpp).
// Target functions of this file:
//   1918  CTextField(const SPoint&, const SharedIText&, const SFont&, TColor, TColor)   (here; its throw is the record
//         at line 30, column 15, so the ctor's position in this file is fixed)
//   10947 GetTypeName() const                                   (here)
//   10950 / 10948  ~CTextField() (complete / deleting; implicit, emitted with the vtable)
//   10952 Draw(IScreen&) const                                  (pending)
//   10951 Rect() const     record at line 55, col 21; calls fn 3889, not named yet   (pending)
//   2241  Move(const SPoint&)  one body binaryen shares with CImageField, CDSImageField, CImageFieldUpdate (pending)
// The pending members are defined in src/units/27-uenux2-ctextfield-pending.cpp.

#include "api/gui/ctextfield.h"

#include "api/gui/eueguierror.h"

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

} // namespace api
