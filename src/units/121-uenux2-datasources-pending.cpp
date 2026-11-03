// Pending members of vota::CEscolheOpcao (src/units/121-uenux2-datasources.mk), each a slot of the vtable
// cescolheopcao.cpp emits with the out-of-line destructor, one trap each so that the class links. The object compiles
// with the unit's flags. What each waits for:
// - vota::CEscolheOpcao::ProcessInput 10689 (slot 7): its direct callees are named but fn 2502, a 15-byte thunk into
//   binaryen's fn 6113 that logs "Operador selecionou: {}" (a CLogVota member), which the target merged with fn 3258
//   ("Mesário {} habilitou o eleitor", called only by fn 10451, not written): without 3258 our 2502 is a whole body,
//   named only by 10689's own call. And it holds vota::CContadoresBiometria::GetInst inlined, whose constructor passes
//   fns 10701, 10700 and 10699 by table slot (3818 to 3820): 10701 and 10700 call comum::CEleitores counters with no
//   name, fns 2821 and 1935. It holds the GetInst of CIniciaFinalizacao, CConfirmaAudio and
//   CHabilitacaoAudioNaoPermitida inlined too (unit 277 writes their other slots and sinks their vtables).
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

void CEscolheOpcao::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
