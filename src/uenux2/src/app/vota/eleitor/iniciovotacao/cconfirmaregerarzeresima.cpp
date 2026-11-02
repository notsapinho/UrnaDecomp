#include "app/vota/eleitor/iniciovotacao/cconfirmaregerarzeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/cregerarzeresima.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CConfirmaRegerarZeresima::CConfirmaRegerarZeresima()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(CTelasVota::GetInst().GetTelaConfirmaRegerarZeresima())
{
}

CConfirmaRegerarZeresima::~CConfirmaRegerarZeresima() = default;

CConfirmaRegerarZeresima& CConfirmaRegerarZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaRegerarZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CConfirmaRegerarZeresima> CConfirmaRegerarZeresima::s_inst;
std::mutex CConfirmaRegerarZeresima::s_mutex;

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
