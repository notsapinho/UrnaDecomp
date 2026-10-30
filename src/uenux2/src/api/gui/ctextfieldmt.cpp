// api::CTextFieldMT (/home/rubio/tse/uenux2/src/api/gui/ctextfieldmt.cpp).
//   1262  CTextFieldMT(const SPoint&, const SharedIText&)   (here; its throw is the record at line 25, column 15)
//   10933 / 10932  ~CTextFieldMT() (complete / deleting; implicit, emitted with the vtable)
//   10934 Draw(IScreenMT&) const                            (here: the key function, so this object emits the vtable)
//   11051 IFormField<IScreenMT>::GetTypeName() const        (slot 7, inline in api/gui/iformfield.h)

#include "api/gui/ctextfieldmt.h"

#include "api/gui/cfixedtext.h"
#include "api/gui/eueguierror.h"
#include "api/gui/iscreenmt.h"

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

void CTextFieldMT::Draw(IScreenMT& screen) const
{
    if (m_textDesenhado && m_textDesenhado->GetText().size() > m_text->GetText().size()) {
        screen.ShowText(m_posicaoDesenhada,
                        CFixedText(std::string(m_textDesenhado->GetText().size(), ' '), m_textDesenhado->GetAlignment()));
    }
    screen.ShowText(m_posicao, *m_text);
    m_textDesenhado = m_text;
    m_posicaoDesenhada = m_posicao;
}

} // namespace api
