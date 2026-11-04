// Pending members of the classes of src/units/161-uenux2-app-vota-operador-identidade.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
// What each waits for is a callee with no body here (ledger/callgraph.tsv against splat/matched.txt and
// splat/symbol_addrs.txt); fn 652, which one of them calls, matches now:
//
// - vota::IEleitorImpedidoVotar::StartState (target fn 10625, slot 2 of the base and of its six derived classes): it
//   calls fn 3616.
#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

void IEleitorImpedidoVotar::StartState()
{
    __builtin_trap();
}

} // namespace vota
