#include "app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.h"

#include "api/gui/cinteractiveform.h"
#include "api/hwil/ibeep.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CInformacaoZeresimaTardia::CInformacaoZeresimaTardia()
    : comum::CAppState(EVENTO_ENTRADA), m_espera(1000), m_form(CTelasVota::GetInst().GetTelaInformacaoZeresimaTardia())
{
}

CInformacaoZeresimaTardia& CInformacaoZeresimaTardia::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInformacaoZeresimaTardia());
    }
    return *s_inst;
}

std::unique_ptr<CInformacaoZeresimaTardia> CInformacaoZeresimaTardia::s_inst;
std::mutex CInformacaoZeresimaTardia::s_mutex;

CInformacaoZeresimaTardia::~CInformacaoZeresimaTardia() = default;

void CInformacaoZeresimaTardia::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

// (original lines 37-40: content not recovered)
#line 41
void CInformacaoZeresimaTardia::ProcessInput()
{
    switch (m_form->Read()) {
        case api::INPUT_CONFIRMA: {
            CLogVota::GetInst().LogaFinalizacaoAplicativo();
            CLogVota::GetInst().LogaDesligandoUrna();

            api::CPolySingleton<api::IBeep>::instance().BeepAlert();
            m_espera.Wait();

            comum::IInterfaceInit& poIni = api::CPolySingleton<comum::IInterfaceInit>::instance();
            poIni.DesligarUrna();
            m_pNextState = nullptr;
            break;
        }
        default:
            break;
    }
}

} // namespace vota
