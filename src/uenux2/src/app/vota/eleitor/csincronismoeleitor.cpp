// vota::CSincronismoEleitor's ProcessKey and StartState (target fns 7181 and 7178), with GetInst and its statics (held
// inlined by fn 4454). The reconstruction's note: no record names this file, and
// src/units/192-uenux2-app-vota-estados-sincronismo.mk says what is chosen.
#include "app/vota/eleitor/csincronismoeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cprogressbar.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/cfimvotoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/isincronismovotoeleitor.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CSincronismoEleitor& CSincronismoEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CSincronismoEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CSincronismoEleitor> CSincronismoEleitor::s_inst;
std::mutex CSincronismoEleitor::s_mutex;

void CSincronismoEleitor::ProcessKey(uebyte tecla)
{
    m_pNextState = this;
    if (tecla == 5 && impl::ISincronismoVotoEleitor::GetInst().Sincroniza()) {
        m_pNextState = &CFimVotoEleitor::GetInst();
    }
}

void CSincronismoEleitor::StartState()
{
    CThreadOperador::GetInst().GetMensagens().Post(13);
    m_pNextState = this;

    CTelasVota& telas = CTelasVota::GetInst();
    const std::shared_ptr<api::CProgressBar>& barra = telas.GetBarraSincronismo();
    barra->SetValor(barra->GetLimiteInferior());
    telas.GetTelaSincronismo()->Slot2();
}

} // namespace vota
