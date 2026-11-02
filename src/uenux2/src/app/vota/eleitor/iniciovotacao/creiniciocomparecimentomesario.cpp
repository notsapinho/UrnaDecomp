#include "app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.h"

#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CReinicioComparecimentoMesario::CReinicioComparecimentoMesario()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CReinicioComparecimentoMesario& CReinicioComparecimentoMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReinicioComparecimentoMesario());
    }
    return *s_inst;
}

std::unique_ptr<CReinicioComparecimentoMesario> CReinicioComparecimentoMesario::s_inst;
std::mutex CReinicioComparecimentoMesario::s_mutex;

void CReinicioComparecimentoMesario::StartState()
{
    m_pNextState = &CAguardaMensagem::GetInst();
    CThreadOperador::GetInst().GetMensagens().Post(7);
}

} // namespace vota
