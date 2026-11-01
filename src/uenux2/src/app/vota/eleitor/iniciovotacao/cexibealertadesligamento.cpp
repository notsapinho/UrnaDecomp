#include "app/vota/eleitor/iniciovotacao/cexibealertadesligamento.h"

#include <chrono>

#include "api/gui/cinteractiveform.h"
#include "api/hwil/ibeep.h"
#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CExibeAlertaDesligamento::CExibeAlertaDesligamento()
    : comum::CAppState(EVENTO_TICK)
    , m_limite(-1)
    , m_form(CTelasVota::GetInst().GetTelaAlertaDesligamento())
    , m_tick(CThreadEleitor::GetInst().AddTick(std::chrono::milliseconds(1000)))
    , m_pProximoEstado(nullptr)
{
}

CExibeAlertaDesligamento& CExibeAlertaDesligamento::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CExibeAlertaDesligamento());
    }
    return *s_inst;
}

std::unique_ptr<CExibeAlertaDesligamento> CExibeAlertaDesligamento::s_inst;
std::mutex CExibeAlertaDesligamento::s_mutex;

CExibeAlertaDesligamento::~CExibeAlertaDesligamento() = default;

void CExibeAlertaDesligamento::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_limite = g_dataHoraDesligamento;
    api::CPolySingleton<api::IBeep>::instance().Beep(2000, 100);
}

void CExibeAlertaDesligamento::ProcessTick(uebyte tick)
{
    if (tick == m_tick) {
        if (m_limite < api::CDateTime::Now()) {
            CLogVota::GetInst().LogaTempoLimiteBateriaInterna();
            api::CPolySingleton<comum::IInterfaceInit>::instance().DesligarUrna();
        } else if (not api::CPolySingleton<api::IPower>::instance().UsandoBateriaInterna()) {
            m_pNextState = m_pProximoEstado;
        }
    }
}

} // namespace vota
