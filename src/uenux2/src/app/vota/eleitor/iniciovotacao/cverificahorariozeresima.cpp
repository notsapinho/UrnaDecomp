#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"

#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {












































































CVerificaHorarioZeresima::~CVerificaHorarioZeresima() = default;

void CVerificaHorarioZeresima::FinishState()
{
    CThreadEleitor::GetInst().StopTick(m_tickHorario);
}

} // namespace vota

// <stubs>
// f5947 · 212 B · unmatched · placement: link order · name unknown
// ? f5947() { ... }
// </stubs>
