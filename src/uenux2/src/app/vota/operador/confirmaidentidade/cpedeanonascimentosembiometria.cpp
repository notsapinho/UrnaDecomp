#include "app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.h"

#include "api/gui/cinteractiveform.h"

namespace vota {

CPedeAnoNascimentoSemBiometria::~CPedeAnoNascimentoSemBiometria() = default;

void CPedeAnoNascimentoSemBiometria::StartState()
{
    m_pNextState = this;
    m_bPrimeira = true;
    m_tentativas = 0;
    m_form->Slot2();
}

} // namespace vota
