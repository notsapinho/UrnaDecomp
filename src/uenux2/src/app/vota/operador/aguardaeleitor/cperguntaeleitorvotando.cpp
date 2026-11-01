#include "app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CPerguntaEleitorVotando::~CPerguntaEleitorVotando() = default;

void CPerguntaEleitorVotando::StartState()
{
    CLogVota::GetInst().LogaIndagaEleitorVotando();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
