#include "app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.h"

#include "api/gui/cinteractiveform.h"
#include "api/hwil/ibeep.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CInformacaoZeresimaTardia::~CInformacaoZeresimaTardia() = default;

void CInformacaoZeresimaTardia::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

// (original lines 19-40: content not recovered)
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
