// vota::CMostraTelaContinuaVotacao: no record names this file or any of its members; the reconstruction's notes are in
// cmostratelacontinuavotacao.h and unit 174's fragment.
#include "app/vota/eleitor/cmostratelacontinuavotacao.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CMostraTelaContinuaVotacao::~CMostraTelaContinuaVotacao() = default;

CMostraTelaContinuaVotacao& CMostraTelaContinuaVotacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMostraTelaContinuaVotacao());
    }
    return *s_inst;
}

CMostraTelaContinuaVotacao::CMostraTelaContinuaVotacao()
    : comum::CAppState(EVENTO_NENHUM)
    , m_form(CTelasVota::GetInst().GetTelaContinuaVotacao())
{
}

std::unique_ptr<CMostraTelaContinuaVotacao> CMostraTelaContinuaVotacao::s_inst;
std::mutex CMostraTelaContinuaVotacao::s_mutex;

void CMostraTelaContinuaVotacao::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    CThreadOperador::GetInst().GetMensagens().Post(12);
    m_pNextState = &CAguardaMensagem::GetInst();
}

} // namespace vota
