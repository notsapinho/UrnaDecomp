#include "app/vota/eleitor/caguardamensagem.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/celeitorvotando.h"
#include "app/vota/eleitor/cinspecionaurna.h"
#include "app/vota/eleitor/ciniciodeciclo.h"
#include "app/vota/eleitor/cmostratelacontinuavotacao.h"
#include "app/vota/eleitor/fimvotacao/cgerabu.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CAguardaMensagem::CAguardaMensagem()
    : comum::CAppState(EVENTO_TECLA)
{
}

CAguardaMensagem& CAguardaMensagem::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAguardaMensagem());
    }
    return *s_inst;
}

std::unique_ptr<CAguardaMensagem> CAguardaMensagem::s_inst;
std::mutex CAguardaMensagem::s_mutex;

void CAguardaMensagem::StartState()
{
    m_pNextState = this;
}

void CAguardaMensagem::ProcessKey(uebyte tecla)
{
    switch (tecla) {
    case 7:
        comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVGERARBU);
        CSincronizaVota::SincronizaEstadoGeralVota();
        CLogVota::GetInst().LogaInicioEncerramento();
        m_pNextState = &CGeraBU::GetInst();
        break;
    case 1:
        CLogVota::GetInst().LogaEleitorHabilitado();
        m_pNextState = &CEleitorVotando::GetInst();
        break;
    case 11:
        m_pNextState = &CIniciodeCiclo::GetInst();
        break;
    case 12:
        m_pNextState = &CInspecionaUrna::GetInst();
        break;
    case 14:
        m_pNextState = &CMostraTelaContinuaVotacao::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
