#include "app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CInformaAnoNascimentoErrado::~CInformaAnoNascimentoErrado() = default;

void CInformaAnoNascimentoErrado::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CInformaAnoNascimentoErrado::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota
