// Pending member: vota::CEleitorVotouNaoVotou::ProcessInput (target fn 10430, slot 7, reached only through the vtable),
// which src/uenux2/src/app/vota/operador/aguardaeleitor/celeitorvotounaovotou.cpp does not hold yet. The class's vtable
// is emitted there and needs it defined; this body is NOT the target's, it traps. The target's reads the form's input
// (api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read, record cinteractiveform.h:57, inlined) and on the
// result 9 goes to one of two states (fns 5393, unit 152's, and 652). It waits for CInteractiveForm's Read (unit 120
// writes the class's other members) and fn 652, not in this tree yet; its api::IInputMT source, fn 383, is.
// Move it into celeitorvotounaovotou.cpp when it is reconstructed.
//
// Delete this file when it moves.
#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"

namespace vota {

void CEleitorVotouNaoVotou::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
