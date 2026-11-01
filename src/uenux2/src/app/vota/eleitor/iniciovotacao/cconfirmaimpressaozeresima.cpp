#include "app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CConfirmaImpressaoZeresima::~CConfirmaImpressaoZeresima() = default;

void CConfirmaImpressaoZeresima::StartState()
{
    CLogVota::GetInst().LogaAguardandoConfirmacaoZeresima();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota

// <stubs>
// f5959 · 177 B · unmatched · placement: link order · name unknown
// ? f5959() { ... }
// </stubs>
