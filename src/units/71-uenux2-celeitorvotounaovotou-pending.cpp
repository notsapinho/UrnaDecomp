// Pending member: comum::IPedeTituloMesario::ProcessInput (target fn 10313, slot 7, 6002 B, the states
// CPedeTituloMesarioInicial, CPedeTituloMesarioFinal and CPedeTituloMesarioVotacao inherit it), which
// src/uenux2/src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp does not hold yet: the same read of the
// form, then the mesario's title against the register. It waits for CInteractiveForm's Read and for the states it
// goes to; the anonymous-namespace GetControlador that its records put at line 30 of that file is inlined into it.
//
// Delete this file when the last of the two moves.
#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"

namespace comum {

void IPedeTituloMesario::ProcessInput()
{
    __builtin_trap();
}

} // namespace comum
