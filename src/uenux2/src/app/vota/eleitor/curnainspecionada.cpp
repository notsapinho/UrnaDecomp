#include "app/vota/eleitor/curnainspecionada.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CUrnaInspecionada::~CUrnaInspecionada() = default;

CUrnaInspecionada& CUrnaInspecionada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CUrnaInspecionada());
    }
    return *s_inst;
}

CUrnaInspecionada::CUrnaInspecionada()
    : comum::CAppState(EVENTO_TECLA)
    , m_form(CTelasVota::GetInst().GetTelaInspecaoTerminada())
    , m_formConfirmacao(CTelasVota::GetInst().GetTelaContinuaVotacao())
{
}

std::unique_ptr<CUrnaInspecionada> CUrnaInspecionada::s_inst;
std::mutex CUrnaInspecionada::s_mutex;

void CUrnaInspecionada::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CUrnaInspecionada::ProcessKey(uebyte tecla)
{
    if (tecla == 13) {
        m_formConfirmacao->Slot2();
        m_pNextState = &CAguardaMensagem::GetInst();
    }
}

} // namespace vota
