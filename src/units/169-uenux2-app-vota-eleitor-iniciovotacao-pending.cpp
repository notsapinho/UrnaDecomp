// Pending members of the zeresima states of src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk, each reached only
// through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move
// each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CGeraZeresimaBase::StartState (target fn 11946, slot 2, 6878 B): it reaches fns 11975 and 11976 by table slot
//   (1632, 1631), which are not written, and no written form of it matches yet;
//   src/units/325-uenux2-geradores-zeresima.mk has the forms measured and what each left.
//   vota::CGeraResumoZeresimaBase::StartState (fn 11943) is written since.
#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"

namespace vota {

void CGeraZeresimaBase::StartState()
{
    __builtin_trap();
}

} // namespace vota
