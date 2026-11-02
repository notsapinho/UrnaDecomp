#include "app/vota/operador/csincronismooperador.h"

#include "api/ipc/cmessagequeue.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {

CSincronismoOperador::CSincronismoOperador()
    : comum::CAppState(EVENTO_TECLA)
    , m_bSincronizado(false)
{
}

CSincronismoOperador& CSincronismoOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CSincronismoOperador());
    }
    return *s_inst;
}

std::unique_ptr<CSincronismoOperador> CSincronismoOperador::s_inst;
std::mutex CSincronismoOperador::s_mutex;

void CSincronismoOperador::StartState()
{
    if (!(comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO &&
          comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor())) {
        comum::CEleitores::GetInst().MarcaVotou();
    }

    CThreadEleitor::GetInst().GetMensagens().Post(5);
    m_pNextState = this;
}

} // namespace vota
