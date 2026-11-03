// Pending members of the zeresima states of src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk, each reached only
// through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move
// each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CConfirmaImpressaoZeresima::ProcessInput (target fn 11927, slot 7): the same Read() (record @1544768); it calls
//   fn 491, named now (unit 205), and holds vota::CImpressaoZeresimaTardia's GetInst inlined (unit 176's class, whose
//   constructor copies a member of vota::CTelasVota that app/vota/eleitor/comum/ctelasvota.h has no accessor for).
// - vota::CQuerImprimirZeresima::ProcessInput (fn 11920, slot 7): the same Read() (record @1544896); it calls fn 491,
//   named now (unit 205), and 2880 (vota::CInicioVotacao::GetInst, unit 199).
// - vota::CGeraZeresimaBase::StartState (target fn 11946, slot 2, 6878 B) and vota::CGeraResumoZeresimaBase::StartState
//   (fn 11943, 1731 B): they call fns 183 and 436, which have names, 11943 also 491 (named now: unit 205), and others that have no name.
// - vota::CGeraResumoZeresima::AposGeracao (target fn 11940, slot 9): it calls fn 491, named now (unit 205).
#include "app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.h"
#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresima.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"
#include "app/vota/eleitor/iniciovotacao/cquerimprimirzeresima.h"

namespace vota {

void CGeraZeresimaBase::StartState()
{
    __builtin_trap();
}

void CGeraResumoZeresimaBase::StartState()
{
    __builtin_trap();
}

void CGeraResumoZeresima::AposGeracao()
{
    __builtin_trap();
}

void CConfirmaImpressaoZeresima::ProcessInput()
{
    __builtin_trap();
}

void CQuerImprimirZeresima::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
