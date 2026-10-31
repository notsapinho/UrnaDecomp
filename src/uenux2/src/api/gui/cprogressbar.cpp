#include "api/gui/cprogressbar.h"

#include "api/gui/iform.h"

namespace api {








































































CProgressBar::~CProgressBar() = default;

void CProgressBar::Move(const SPoint& posicao)
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

SRect CProgressBar::Rect() const
{
    return m_rect;
}

void CProgressBar::Limita()
{
    if (m_valor < m_limiteInferior) {
        m_valor = m_limiteInferior;
    } else if (m_valor > m_limiteSuperior) {
        m_valor = m_limiteSuperior;
    }
}

void CProgressBar::SetValor(const uedword valor)
{
    if (m_valor == valor) {
        return;
    }

    m_valor = valor;
    Limita();

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

void CProgressBar::Incrementa()
{
    ++m_valor;
    Limita();

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

} // namespace api
