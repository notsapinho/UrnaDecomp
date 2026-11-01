// vota::CMostraTelaContinuaVotacao: no record names this file or any of its members; the reconstruction's notes are in
// cmostratelacontinuavotacao.h and unit 174's fragment.
#include "app/vota/eleitor/cmostratelacontinuavotacao.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CMostraTelaContinuaVotacao::~CMostraTelaContinuaVotacao() = default;

void CMostraTelaContinuaVotacao::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    CThreadOperador::GetInst().GetMensagens().Post(12);
    m_pNextState = &CAguardaMensagem::GetInst();
}

} // namespace vota
