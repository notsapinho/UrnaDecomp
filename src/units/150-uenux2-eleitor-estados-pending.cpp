// Pending members of unit 150: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables.
//
// vota::CVisualizarCandidatos, in src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.cpp:
// - StartState 11876 (slot 2, records :132 and :140), 927 B: calls fn 6569 twice, which has no name, and fn 455.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

namespace vota {

void CVisualizarCandidatos::StartState()
{
    __builtin_trap();
}

} // namespace vota
