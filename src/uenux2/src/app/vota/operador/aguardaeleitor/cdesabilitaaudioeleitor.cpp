#include "app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CDesabilitaAudioEleitor::~CDesabilitaAudioEleitor() = default;

void CDesabilitaAudioEleitor::StartState()
{
    CLogVota::GetInst().LogaPedidoDesconexaoFone();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota

// <stubs>
// f5393 · 652 B · unmatched · placement: link order · name unknown
// ? f5393() { ... }
// </stubs>
