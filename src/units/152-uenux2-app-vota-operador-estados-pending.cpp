// Pending members of the classes of src/units/152-uenux2-app-vota-operador-estados.mk, each reached only through its
// vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move each into
// its class's .cpp when it is reconstructed, and delete this file with the last. What each waits for is a callee with
// no name (ledger/callgraph.tsv against splat/symbol_addrs.txt). Fn 501, which it calls, matches now
// (api::CPriorityMessageQueue<api::SMessage>::Insert, named by its callers' calls:
// src/units/269-uenux2-cmessagequeue-insert.mk):
// - vota::CInspecionaUrna::ProcessInput (fn 11797, slot 7): fn 6557 (2380, vota::TelaNeutra in ctelasvota.cpp, is
//   named since).
#include "app/vota/eleitor/cinspecionaurna.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

namespace vota {

void CInspecionaUrna::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
