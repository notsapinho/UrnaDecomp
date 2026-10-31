#include "app/vota/eleitor/fimvotacao/caplicacaoencerrada.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CAplicacaoEncerrada::~CAplicacaoEncerrada() = default;

void CAplicacaoEncerrada::StartState()
{
    m_pNextState = this;
    CLogVota::GetInst().LogaVotacaoEncerrada();
    m_form->Slot2();
}

} // namespace vota

// <stubs>
// f3877 · 140 B · unmatched · placement: link order · name unknown
// ? f3877() { ... }
// </stubs>
