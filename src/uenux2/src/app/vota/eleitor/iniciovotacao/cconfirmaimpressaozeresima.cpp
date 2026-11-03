#include "app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresima.h"
#include "app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.h"
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

void CConfirmaImpressaoZeresima::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (api::CDateTime::Now() > m_limite) {
            m_pNextState = &CImpressaoZeresimaTardia::GetInst();
        } else {
            comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVGERARZE);
            CSincronizaVota::SincronizaEstadoGeralVota();
            m_pNextState = &CGeraZeresima::GetInst();
        }
        break;
    case api::INPUT_BRANCO:
        m_pNextState = &CMaisInformacoes::GetInst(this);
        break;
    default:
        break;
    }
}

} // namespace vota
