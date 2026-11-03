// Pending members of the zeresima states of src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk, each reached only
// through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move
// each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CGeraZeresimaBase::StartState (target fn 11946, slot 2, 6878 B) and vota::CGeraResumoZeresimaBase::StartState
//   (fn 11943, 1731 B): they call fns 183 and 436, which have names, 11943 also 491 (named now: unit 205), and others that have no name.
#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"

namespace vota {

void CGeraZeresimaBase::StartState()
{
    __builtin_trap();
}

void CGeraResumoZeresimaBase::StartState()
{
    __builtin_trap();
}

} // namespace vota
