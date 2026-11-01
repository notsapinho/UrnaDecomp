#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

#include "api/gui/cinteractiveform.h"

namespace vota::testeteclado {

void CBase::StartState()
{
    m_pNextState = this;
    m_form = GetTela();
    m_form->Slot2();
}

CBase::CBase()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
{
}

} // namespace vota::testeteclado
