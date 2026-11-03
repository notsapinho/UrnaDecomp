#include "app/vota/eleitor/fimvotacao/cretirarmr.h"

#include "api/gui/cinteractiveform.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CRetirarMR::~CRetirarMR() = default;

// (original lines 20-48: content not recovered)
#line 49
void CRetirarMR::StartState()
{
    md::estadoaplicacao::CEstadoGeralVota& vota = CAppInfo::GetInst().GetVota();
    vota.SetEstadoEncerramento(EAERETIRAMR);
    CSincronizaVota::SincronizaEstadoGeralVota();
    ASSERT(vota.GetEstadoVota() == EAVENCERRADA, api::EUA_RETIRARMR_ESTADOINVALIDO);
    ASSERT(vota.GetEstadoEncerramento() == EAERETIRAMR, api::EUA_RETIRARMR_ENCERRINVALIDO);
    comum::IInterfaceInit& poIni = api::CPolySingleton<comum::IInterfaceInit>::instance();
    if (poIni.GetDemoMode()) {
        vota.SetEstadoEncerramento(EAEFIMDOSTRABALHOS);
        m_formDemo->Slot2();
    } else {
        m_formRetirar->Slot2();
        CLogVota::GetInst().LogaSolicitadaRetiradaMR();
        AguardaRetiradaMR();
        CLogVota::GetInst().LogaMRRetirada();
        vota.SetEstadoEncerramento(EAEFIMDOSTRABALHOS);
        CSincronizaVota::SincronizaEstadoGeralVota();
        m_form->Slot2();
    }
    m_pNextState = this;
}

// (original lines 72-75: content not recovered)
#line 76
void CRetirarMR::ProcessInput()
{
    bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    api::EInputResult resultado = ehDemo ? m_formDemo->Read() : m_form->Read();
    if (resultado == api::INPUT_CONFIRMA) {
        m_pNextState = &CEmitirMaisBU::GetInst();
    }
}

// (original lines 85-93: content not recovered)
#line 94
bool CRetirarMR::AguardaRetiradaMR()
{
    comum::IInterfaceInit& poIni = api::CPolySingleton<comum::IInterfaceInit>::instance();
    while (poIni.IsMRPresenteSemHabilitar()) {
        api::CSystem::Dorme(250);
    }
    return true;
}

} // namespace vota

// <stubs>
// f2291 · 3426 B · unmatched · placement: link order · name unknown
// ? f2291() { ... }
// </stubs>
