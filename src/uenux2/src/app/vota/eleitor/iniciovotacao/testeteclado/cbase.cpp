#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.h"
#include "app/vota/log/clogvota.h"

namespace vota::testeteclado {

void CBase::StartState()
{
    m_pNextState = this;
    m_form = GetTela();
    m_form->Slot2();
}

void CBase::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        m_pNextState = GetEstadoSemTeste();
        if (GetNextState() != this) {
            CLogVota::GetInst().LogaTesteTecladoNaoExecutado();
        }
        break;
    case api::INPUT_CONFIRMA: {
        comum::CAppState* const estado = GetEstadoPassouNoTeste();
        CTesteTeclado::GetInst().SetEstadoPassouNoTeste(estado);
        m_pNextState = &CTesteTeclado::GetInst();
        break;
    }
    default:
        break;
    }
}

CBase::CBase()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
{
}

} // namespace vota::testeteclado
