// Fragment 174's members that are not written yet. Each traps, so no match can land on it, and each moves into its
// class's .cpp when it is written. What each holds and waits for (the target's bodies, read with pnpm wasm fn):
// - vota::IConfirmaJustificativa::StartState, fn 10589 (slot 2 of the class and of its three derived classes): calls the
//   form's slot 2 (+12), then fn 3616, and stores `this` at +4; waits for fn 3616 (3477 B), which has no name.
#include "app/vota/operador/justificativa/iconfirmajustificativa.h"

namespace vota {

void IConfirmaJustificativa::StartState()
{
    __builtin_trap();
}

} // namespace vota
