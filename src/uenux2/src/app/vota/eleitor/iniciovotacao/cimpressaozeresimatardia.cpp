#include "app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresima.h"
#include "app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImpressaoZeresimaTardia::~CImpressaoZeresimaTardia() = default;

CImpressaoZeresimaTardia::CImpressaoZeresimaTardia()
    : comum::CAppState(EVENTO_ENTRADA), m_form(CTelasVota::GetInst().GetTelaImpressaoZeresimaTardia())
{
}

CImpressaoZeresimaTardia& CImpressaoZeresimaTardia::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoZeresimaTardia());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoZeresimaTardia> CImpressaoZeresimaTardia::s_inst;
std::mutex CImpressaoZeresimaTardia::s_mutex;

void CImpressaoZeresimaTardia::StartState()
{
    CLogVota::GetInst().LogaMesarioIndagadoHorarioUrna();
    m_form->Slot2();
    m_pNextState = this;
}

void CImpressaoZeresimaTardia::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaMesarioConfirmaHorarioUrnaErrado();
        m_pNextState = &CInformacaoZeresimaTardia::GetInst();
        break;
    case api::INPUT_CONFIRMA:
        comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVGERARZE);
        CSincronizaVota::SincronizaEstadoGeralVota();
        CLogVota::GetInst().LogaMesarioConfirmaHorarioUrnaCorreto();
        m_pNextState = &CGeraZeresima::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
