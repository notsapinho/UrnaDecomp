#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CHabilitaAudioEleitor::~CHabilitaAudioEleitor() = default;

void CHabilitaAudioEleitor::StartState()
{
    CLogVota::GetInst().LogaPedidoConexaoFone();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota

// <stubs>
// f2743 · 882 B · unmatched · placement: link order · name unknown
// ? f2743() { ... }
// </stubs>
