// Pending members of unit 199 (src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk): the slots the unit's
// vtables need and no reconstructed source holds yet. Their bodies are NOT the target's, they trap. All are reached only
// through the vtables; StartState is CGeraDadosDinamicos's key function, so this object emits that class's vtable and
// typeinfo, with no change when the member lands (src/units/README.md "Pending members").
//
// vota::CGeraDadosDinamicos, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.cpp:
// - StartState 11865 (slot 2, record :47, whose line stays blank there): not written, though every callee has a name
//   now: 6737 (vota::CEstadoAudio::GeraDadosDinamicos, unit 116), 6734 (CarregaEleitores, fragment 386), fn 491 (unit
//   205), vota::CEstadoAudio::GetInst (fn 509), an api::EUeAssertError throw and CVerificaHorarioZeresima::GetInst
//   (fn 5947, unit 138).
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.h"

namespace vota {

void CGeraDadosDinamicos::StartState()
{
    __builtin_trap();
}

} // namespace vota
