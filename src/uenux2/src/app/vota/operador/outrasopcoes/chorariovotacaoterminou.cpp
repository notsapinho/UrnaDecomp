#include "app/vota/operador/outrasopcoes/chorariovotacaoterminou.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CHorarioVotacaoTerminou::~CHorarioVotacaoTerminou() = default;

void CHorarioVotacaoTerminou::StartState()
{
    CLogVota::GetInst().LogaHorarioVotacaoTerminou();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota

// <stubs>
// f5430 · 948 B · unmatched · placement: link order · name unknown
// ? f5430() { ... }
// </stubs>
