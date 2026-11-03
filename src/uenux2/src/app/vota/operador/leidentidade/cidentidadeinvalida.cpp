#include "app/vota/operador/leidentidade/cidentidadeinvalida.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CIdentidadeInvalida::~CIdentidadeInvalida() = default;

void CIdentidadeInvalida::StartState()
{
    CLogVota::GetInst().LogaIdentificadorEleitorInvalido();
    m_form->Slot2();
    m_pNextState = this;
}

void CIdentidadeInvalida::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
