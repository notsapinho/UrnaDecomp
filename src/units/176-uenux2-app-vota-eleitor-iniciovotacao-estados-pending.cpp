// Pending members of the iniciovotacao states of src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk, each
// reached only through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they
// trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last. StartState is the
// key function of two of the vota::CImpressao* states, so this object emits their vtables and typeinfos;
// vota::CImpressaoVersaoPacotes's StartState (fn 11905) and vota::CImpressaoEstadoUrna's (fn 11911) are written, in
// their classes' .cpp.
//
// - vota::CImpressaoListaEleitores::StartState (fn 11908, 4670 B) and vota::CImpressaoPU::StartState (fn 11902, 6548 B),
//   not read for this unit.
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.h"

namespace vota {

void CImpressaoListaEleitores::StartState()
{
    __builtin_trap();
}

void CImpressaoPU::StartState()
{
    __builtin_trap();
}

} // namespace vota
