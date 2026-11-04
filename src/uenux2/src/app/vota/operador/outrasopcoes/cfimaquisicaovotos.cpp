#include "app/vota/operador/outrasopcoes/cfimaquisicaovotos.h"

#include "api/ipc/cmessagequeue.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/cfinalizaoperador.h"

namespace vota {

CFimAquisicaoVotos::CFimAquisicaoVotos()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFimAquisicaoVotos& CFimAquisicaoVotos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFimAquisicaoVotos());
    }
    return *s_inst;
}

std::unique_ptr<CFimAquisicaoVotos> CFimAquisicaoVotos::s_inst;
std::mutex CFimAquisicaoVotos::s_mutex;

void CFimAquisicaoVotos::StartState()
{
    if (RegistraMesarios()) {
        SetNextState(&comum::CRegistrarMesarios::GetInst());
        return;
    }
    CThreadEleitor::GetInst().GetMensagens().Post(7);
    SetNextState(&CFinalizaOperador::GetInst());
}

} // namespace vota
