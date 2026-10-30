// api::CImageField (/home/rubio/tse/uenux2/src/api/gui/cimagefield.cpp, named by the record of Rect at line 52).
// Target functions of this file:
//   2242  CImageField(const SPoint&, const SharedIImage&, EAnchorPoint)   (here; no record: it stores CImageField's vptr
//         over the IFormFieldBase members, and its parameter types are CImageFieldUpdate's and CDSImageField's records')
//   11099 / 11098  ~CImageField() (complete / deleting; implicit, emitted with the vtable, which the pending
//         GetTypeName, the class's key function, puts in the pending object until it moves here)
//   11097 GetTypeName() const   a call into fn 2904, the body binaryen's merge-similar-functions made of four
//                               functions that return an 11-character name; our link keeps it unmerged     (pending)
//   11102 Draw(IScreen&) const  calls IScreen slots 22 and 24, two of iscreen.h's DrawImage overloads      (here)
//   11101 Rect() const          record at line 52, col 12: CPolySingleton<IScreen>::instance() (fn 512)  (pending)
//   2241  Move(const SPoint&)   one body binaryen shares with CTextField, CImageFieldUpdate, CTextFieldBlinking and
//                               CTextFieldUpdate; CDSImageField inherits it   (here, below Rect's line: a choice)
// The pending members are defined in src/units/29-uenux2-cimagefield-pending.cpp.

#include "api/gui/cimagefield.h"

#include "api/gui/iform.h"
#include "api/gui/iscreen.h"

namespace api {

/**
 * Cria um campo que desenha @p imagem em @p posicao.
 *
 * @param posicao posição da tela onde a imagem é desenhada
 * @param imagem imagem do campo; pode ser nula, e então nada é desenhado
 * @param ancora ponto da imagem que fica em @p posicao
 */
CImageField::CImageField(const SPoint& posicao, const SharedIImage& imagem, EAnchorPoint ancora)
    : m_posicao(posicao)
    , m_imagem(imagem)
    , m_ancora(ancora)
{
}

void CImageField::Draw(IScreen& screen) const
{
    if (m_imagem == nullptr) {
        return;
    }

    if (m_tamanho == nullptr) {
        screen.DrawImage(m_posicao, *m_imagem, m_ancora);
    } else {
        screen.DrawImage(m_posicao, *m_imagem, *m_tamanho, m_ancora);
    }
}










void CImageField::Move(const SPoint& posicao)
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
