// Pending members of fragment 165's classes, each a slot of a vtable the unit emits (src/units/165-uenux2-app-vota-execucao.mk).
// What each waits for:
// - vota::CAguardaInicio::ProcessKey 10217 (slot 6), 191 B: key 7 goes to the state fn 3610 returns, key 8 logs
//   "Urna pronta para receber votos" (comum::IEventosLog::loga, fn 233, on vota::CLogVota::GetInst, fn 184) and goes to
//   the state fn 652 returns, key 10 goes to vota::CFimAquisicaoVotos::GetInst (fn 5428). Fns 652 and 3610, two states'
//   GetInst, have no name.
#include "app/vota/iexecucaovota.h"
#include "app/vota/operador/caguardainicio.h"

namespace vota {

void CAguardaInicio::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
