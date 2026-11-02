// vota::CSincronismoEleitor's StartState (target fn 7178). The reconstruction's note: no record names this file, and
// src/units/192-uenux2-app-vota-estados-sincronismo.mk says what is chosen.
#include "app/vota/eleitor/csincronismoeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cprogressbar.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

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
