// Pending member: vota::CEleitorVotouNaoVotou::ProcessInput (target fn 10430, slot 7, reached only through the vtable),
// which src/uenux2/src/app/vota/operador/aguardaeleitor/celeitorvotounaovotou.cpp does not hold yet. The class's vtable
// is emitted there and needs it defined; this body is NOT the target's, it traps. The target's reads the form's input
// (api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read, record cinteractiveform.h:57, inlined) and on the
// result 9 goes to one of two states (fns 5393 and 652). It waits for CInteractiveForm's members and fields, its
// api::IInputMT source (fn 383) and those two states, none of them in this tree yet.
// Move it into celeitorvotounaovotou.cpp when it is reconstructed.
//
// Pending member: comum::IPedeTituloMesario::ProcessInput (target fn 10313, slot 7, 6002 B, the states
// CPedeTituloMesarioInicial, CPedeTituloMesarioFinal and CPedeTituloMesarioVotacao inherit it), which
// src/uenux2/src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp does not hold yet: the same read of the
// form, then the mesario's title against the register. It waits for CInteractiveForm's members and for the states it
// goes to; the anonymous-namespace GetControlador that its records put at line 30 of that file is inlined into it.
//
// Delete this file when the last of the two moves.
#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"
#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"

namespace vota {

void CEleitorVotouNaoVotou::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota

namespace comum {

void IPedeTituloMesario::ProcessInput()
{
    __builtin_trap();
}

} // namespace comum
