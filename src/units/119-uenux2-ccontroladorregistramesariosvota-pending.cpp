// vota::CControladorRegistraMesariosVota's slot that is not written yet. It
// traps, so no match can land on it, and it moves into its class's .cpp when it is written. What it holds and waits
// for (the target's body, read with pnpm wasm fn):
// - slot 16, fn 10786: calls fn 4662, which throws an api::CUeDesligandoError that fn 1685 builds when the byte at
//   1832936 is 1, and else calls fn 4657 (1048 B); no callee waits now (4662 is vota::CSincronizaVota's
//   SincronizaBancoDados, unit 205's, as 1685 and 4657 are): not written yet.
#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"

namespace vota {

void CControladorRegistraMesariosVota::Slot16() const
{
    __builtin_trap();
}

} // namespace vota
