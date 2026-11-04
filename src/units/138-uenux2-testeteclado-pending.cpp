// Pending members of unit 138: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables. What each waits for (a callee "with no name"
// has no line in splat/matched.txt or splat/symbol_addrs.txt):
//
// vota::CVerificaHorarioZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp:
// - ProcessInput 11869 (slot 7), 861 B: fn 6595, with no name (and 491, named now: unit 205; 5586, matched: unit 123;
//   5591, matched: unit 296), 455 and 5880 (IEventosLog's).
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"

namespace vota {

void CVerificaHorarioZeresima::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
