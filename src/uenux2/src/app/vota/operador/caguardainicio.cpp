#include "app/vota/operador/caguardainicio.h"

#include "api/gui/iform.h"
#include "api/gui/iscreenmt.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CAguardaInicio::~CAguardaInicio() = default;

void CAguardaInicio::StartState()
{
    m_pNextState = this;
    CThreadOperador::GetInst().StartTick(m_tick);
    m_form->Slot2();
}

void CAguardaInicio::FinishState()
{
    CThreadOperador::GetInst().StopTick(m_tick);
}

void CAguardaInicio::ProcessTick(uebyte id)
{
    if (id == m_tick) {
        m_form->Slot2();
    }
}

} // namespace vota

// <stubs>
// f5343 · 2105 B · unmatched · placement: link order · name unknown
// ? f5343() { ... }
// </stubs>
