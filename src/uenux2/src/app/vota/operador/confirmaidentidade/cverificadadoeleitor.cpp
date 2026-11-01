#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CVerificaDadoEleitor::~CVerificaDadoEleitor() = default;

void CVerificaDadoEleitor::StartState()
{
    CLogVota::GetInst().LogaSolicitacaoDadoPessoalEleitor();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota

// <stubs>
// f2735 · 1413 B · unmatched · placement: link order · name unknown
// ? f2735() { ... }
// </stubs>
