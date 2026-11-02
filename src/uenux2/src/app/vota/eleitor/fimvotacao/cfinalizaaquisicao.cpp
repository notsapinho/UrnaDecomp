// vota::CFinalizaAquisicao: no record names this file or its member; its path is chosen
// (src/units/223-uenux2-cfinalizaaquisicao.mk says why). The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/fimvotacao/cfinalizaaquisicao.h"

#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

void CFinalizaAquisicao::StartState()
{
    m_pNextState = &CAguardaMensagem::GetInst();
    CThreadOperador::GetInst().GetMensagens().Post(10);
}

} // namespace vota
