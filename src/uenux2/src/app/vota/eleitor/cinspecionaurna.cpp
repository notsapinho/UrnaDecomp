#include "app/vota/eleitor/cinspecionaurna.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/curnainspecionada.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CInspecionaUrna::~CInspecionaUrna() = default;

CInspecionaUrna& CInspecionaUrna::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInspecionaUrna());
    }
    return *s_inst;
}

CInspecionaUrna::CInspecionaUrna()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(CTelasVota::GetInst().GetTelaInspecionaUrna())
{
}

std::unique_ptr<CInspecionaUrna> CInspecionaUrna::s_inst;
std::mutex CInspecionaUrna::s_mutex;

void CInspecionaUrna::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
    CLogVota::GetInst().LogaInspecaoIniciada();
}

void CInspecionaUrna::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CUrnaInspecionada::GetInst();
        CLogVota::GetInst().LogaInspecaoUrnaConfirmada();
        CThreadOperador::GetInst().GetMensagens().Post(11);
    }
}

} // namespace vota
