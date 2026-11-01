#include "app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CConfirmaImpressaoZeresima::CConfirmaImpressaoZeresima()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(CTelasVota::GetInst().GetTelaConfirmaImpressaoZeresima())
    , m_limite(comum::CConfiguracaoEleicao::GetInst().GetDataHoraZeresima())
{
    m_limite += 3 * 60 * 60;
}

CConfirmaImpressaoZeresima& CConfirmaImpressaoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaImpressaoZeresima());
    }
    return *s_inst;
}

CConfirmaImpressaoZeresima::~CConfirmaImpressaoZeresima() = default;

std::unique_ptr<CConfirmaImpressaoZeresima> CConfirmaImpressaoZeresima::s_inst;
std::mutex CConfirmaImpressaoZeresima::s_mutex;

void CConfirmaImpressaoZeresima::StartState()
{
    CLogVota::GetInst().LogaAguardandoConfirmacaoZeresima();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
