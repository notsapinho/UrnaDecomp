#include "app/vota/operador/leidentidade/cidentidadeinvalida.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CIdentidadeInvalida::~CIdentidadeInvalida() = default;

void CIdentidadeInvalida::StartState()
{
    CLogVota::GetInst().LogaIdentificadorEleitorInvalido();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
