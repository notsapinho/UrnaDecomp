// vota::CFinalizaAquisicao: no record names this file or its member; its path is chosen
// (src/units/223-uenux2-cfinalizaaquisicao.mk says why). The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/fimvotacao/cfinalizaaquisicao.h"

#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CFinalizaAquisicao::CFinalizaAquisicao()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFinalizaAquisicao& CFinalizaAquisicao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFinalizaAquisicao());
    }
    return *s_inst;
}

std::unique_ptr<CFinalizaAquisicao> CFinalizaAquisicao::s_inst;
std::mutex CFinalizaAquisicao::s_mutex;

void CFinalizaAquisicao::StartState()
{
    m_pNextState = &CAguardaMensagem::GetInst();
    CThreadOperador::GetInst().GetMensagens().Post(10);
}

} // namespace vota
