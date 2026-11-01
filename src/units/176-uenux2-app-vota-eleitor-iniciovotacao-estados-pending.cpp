// Pending members of the iniciovotacao states of src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk, each
// reached only through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they
// trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last. StartState is the
// key function of the four vota::CImpressao* states, so this object emits their vtables and typeinfos.
//
// - vota::CImpressaoEstadoUrna::StartState (target fn 11911, slot 2, 565 B), vota::CImpressaoListaEleitores::StartState
//   (fn 11908, 4670 B), vota::CImpressaoVersaoPacotes::StartState (fn 11905, 5098 B) and vota::CImpressaoPU::StartState
//   (fn 11902, 6548 B): not read for this unit.
// - vota::CImpressaoZeresimaTardia::ProcessInput (target fn 11931, slot 7): it calls fn 491, which has no name, and holds
//   vota::CInformacaoZeresimaTardia's GetInst inlined, whose constructor copies vota::CTelasVota::GetInst()'s +68, which
//   app/vota/eleitor/comum/ctelasvota.h has no accessor for.
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.h"
#include "app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.h"

namespace vota {

void CImpressaoEstadoUrna::StartState()
{
    __builtin_trap();
}

void CImpressaoListaEleitores::StartState()
{
    __builtin_trap();
}

void CImpressaoVersaoPacotes::StartState()
{
    __builtin_trap();
}

void CImpressaoPU::StartState()
{
    __builtin_trap();
}

void CImpressaoZeresimaTardia::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
