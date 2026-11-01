#include "app/vota/eleitor/iniciovotacao/cconfirmaregerarzeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/cregerarzeresima.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CConfirmaRegerarZeresima::~CConfirmaRegerarZeresima() = default;

void CConfirmaRegerarZeresima::StartState()
{
    CLogVota::GetInst().LogaAguardandoConfirmacaoZeresima();
    m_form->Slot2();
    m_pNextState = this;
}

void CConfirmaRegerarZeresima::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CRegerarZeresima::GetInst();
        break;
    case api::INPUT_BRANCO:
        m_pNextState = &CMaisInformacoes::GetInst(this);
        break;
    default:
        break;
    }
}

} // namespace vota
