// Pending members of the iniciovotacao states of src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk, each
// reached only through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they
// trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last. StartState is the
// key function of vota::CImpressaoListaEleitores, so this object emits its vtable and typeinfo;
// vota::CImpressaoVersaoPacotes's StartState (fn 11905), vota::CImpressaoEstadoUrna's (fn 11911) and
// vota::CImpressaoPU's (fn 11902) are written, in their classes' .cpp.
//
// - vota::CImpressaoListaEleitores::StartState (fn 11908, 4670 B): it builds the std::function<comum::SQtdeAptos()> of
//   a lambda that returns CEleitores::QuantidadeAptos() (fn 2881, RTTI), which celeitores.h declares returning a struct
//   of its own, so it waits for that header. vota::CImpressaoPU::StartState (fn 11902) is written in cimpressaopu.cpp.
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.h"

namespace vota {

void CImpressaoListaEleitores::StartState()
{
    __builtin_trap();
}

} // namespace vota
