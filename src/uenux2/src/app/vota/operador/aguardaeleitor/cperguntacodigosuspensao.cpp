#include "app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CPerguntaCodigoSuspensao::~CPerguntaCodigoSuspensao() = default;

void CPerguntaCodigoSuspensao::StartState()
{
    m_pNextState = this;
    CLogVota::GetInst().LogaPedidoTituloSuspensao();
    m_form->Slot2();
    m_bLido = false;
}

} // namespace vota
