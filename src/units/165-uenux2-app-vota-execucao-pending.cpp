// Pending members of fragment 165's classes, each a slot of a vtable the unit emits (src/units/165-uenux2-app-vota-execucao.mk).
// What each waits for:
// - vota::CExecucaoVota::GetEstadoEleitor 4705 (slot 9), 21 B, one body with vota::CExecucaoVotaCooperativa's slot 9:
//   `CAppState* e = CThreadEleitor::GetInst()'s context (+32); return e ? the context's state (+4) : nullptr;`. It needs
//   a reader of vota::CThreadVota's m_contexto (private, app/vota/cthreadvota.h) and of comum::CAppStateContext's state
//   at +4, which app/comum/cappstatecontext.h does not declare here and another branch's copy keeps private.
// - vota::CExecucaoVotaCooperativa::Executa and IniciaThreads (slots 2 and 3, one body, fn 4713, 89 B):
//   `CThreadEleitor& t = CThreadEleitor::GetInst(); t's context (+32).reset(new comum::CAppStateContext(m_estadoInicial));`
//   then the new context's state, if any, gets StartState. It needs the context's constructor, fn 3844, which
//   app/comum/cappstatecontext.h does not declare here, and a writer of vota::CThreadVota's m_contexto (private).
// - vota::CExecucaoVotaCooperativa::ProcessaEntradaEleitor 7823 (slot 7), 38 B: `false` unless vota::CThreadEleitor has a
//   context and its stop flag (+8) is clear, then CThreadEleitor's ProcessarEntrada (fn 4349, record
//   cthreadeleitor.cpp:134, 1427 B, not written) over that context.
// - vota::CExecucaoVotaCooperativa::GetEstadoEleitor 4705 (slot 9): CExecucaoVota's body, the same wait.
// - vota::CPreShowFormVota::PreShow 7707 (slot 2), 61 B: it calls fn 4620, which has no name. It is the class's key
//   function, so this object emits CPreShowFormVota's vtable, which GetFormularioInterativo (fn 576,
//   app/vota/comum/cpreshowformvota.cpp) stores.
// - vota::CAguardaInicio::ProcessKey 10217 (slot 6), 191 B: key 7 goes to the state fn 3610 returns, key 8 logs
//   "Urna pronta para receber votos" (comum::IEventosLog::loga, fn 233, on vota::CLogVota::GetInst, fn 184) and goes to
//   the state fn 652 returns, key 10 goes to vota::CFimAquisicaoVotos::GetInst (fn 5428). Fns 652 and 3610, two states'
//   GetInst, have no name.
#include "app/vota/cexecucaovotacooperativa.h"
#include "app/vota/comum/cpreshowformvota.h"
#include "app/vota/iexecucaovota.h"
#include "app/vota/operador/caguardainicio.h"

namespace vota {

comum::CAppState* CExecucaoVota::GetEstadoEleitor()
{
    __builtin_trap();
}

void CExecucaoVotaCooperativa::Executa()
{
    __builtin_trap();
}

void CExecucaoVotaCooperativa::IniciaThreads()
{
    __builtin_trap();
}

bool CExecucaoVotaCooperativa::ProcessaEntradaEleitor()
{
    __builtin_trap();
}

comum::CAppState* CExecucaoVotaCooperativa::GetEstadoEleitor()
{
    __builtin_trap();
}

void CAguardaInicio::ProcessKey(uebyte)
{
    __builtin_trap();
}

void CPreShowFormVota::PreShow(api::IScreen&)
{
    __builtin_trap();
}

} // namespace vota
