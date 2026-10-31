// Pending members of the zeresima states of src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk, each reached only
// through its vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move
// each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CInformacaoZeresimaTardia::ProcessInput (target fn 11982, slot 7, records cinformacaozeresimatardia.cpp:48
//   and :51): reads the form through api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read() (record
//   cinteractiveform.h:57 @1543736, inlined), which api/gui/cinteractiveform.h does not hold yet, and calls fns 5446
//   (on the api::CWait at +16) and 5894, which have no name.
// - vota::CConfirmaImpressaoZeresima::ProcessInput (target fn 11927, slot 7): the same Read() (record @1544768).
// - vota::CGeraZeresimaBase::StartState (target fn 11946, slot 2, 6878 B) and vota::CGeraResumoZeresimaBase::StartState
//   (fn 11943, 1731 B): they call fns 183, 436 and 491, which have no name.
// - vota::CGeraResumoZeresima::AposGeracao (target fn 11940, slot 9): it calls fn 491, which has no name.
// - vota::CGeraZeresima::GetProximoEstado (target fn 11935, slot 10): it returns vota::CGeraResumoZeresima::GetInst(),
//   which waits for vota::CGeraResumoZeresimaBase's constructor (cgeraresumozeresimabase.h says why).
#include "app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.h"
#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresima.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresima.h"
#include "app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.h"

namespace vota {

void CInformacaoZeresimaTardia::ProcessInput()
{
    __builtin_trap();
}

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

comum::CAppState* CGeraZeresima::GetProximoEstado()
{
    __builtin_trap();
}

void CConfirmaImpressaoZeresima::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
