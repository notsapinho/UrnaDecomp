#include "app/vota/operador/leidentidade/celeitorjavotou.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CEleitorJaVotou::~CEleitorJaVotou() = default;

void CEleitorJaVotou::StartState()
{
    CLogVota::GetInst().LogaEleitorJaVotou();
    m_form->Slot2();
    m_pNextState = this;
}

void CEleitorJaVotou::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota
