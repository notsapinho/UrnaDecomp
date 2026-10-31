// api::CImageField (/home/rubio/tse/uenux2/src/api/gui/cimagefield.cpp). Target functions of this file:
//   2242  CImageField(const SPoint&, const SharedIImage&, EAnchorPoint)   (here; the fragment has its evidence)
//   11099 / 11098  ~CImageField() (complete / deleting; implicit, emitted with the vtable: Draw is the key function)
//   11097 GetTypeName() const   in the class: a thunk of fn 2904, binaryen's merge of four 11-character names
//   11102 Draw(IScreen&) const  calls IScreen slots 22 and 24, two of iscreen.h's DrawImage overloads      (here)
//   11101 Rect() const          record at line 52, col 12                                                 (here)
//   2241  Move(const SPoint&), one body with four other fields   (here, below Rect's line: a choice)
//   5533  SetImage(SharedIImage)   its two callers are fn 11093 and its thunk   (here, a chosen name and place)

#include "api/gui/cimagefield.h"

#include "api/gui/iform.h"
#include "api/gui/iimagesurfaceops.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"

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

SRect CImageField::Rect() const
{
    if (m_imagem == nullptr) {
        return {};
    }

    return CPolySingleton<IScreen>::instance().GetImageSurfaceOps().ImageRect(*m_imagem, m_posicao, m_ancora);
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

void CImageField::SetImage(SharedIImage imagem)
{
    m_imagem = imagem;

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

} // namespace api
