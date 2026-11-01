// Pending members of unit 199 (src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk): the slots the unit's
// vtables need and no reconstructed source holds yet. Their bodies are NOT the target's, they trap. All are reached only
// through the vtables; StartState is CGeraDadosDinamicos's key function, so this object emits that class's vtable and
// typeinfo, with no change when the member lands (src/units/README.md "Pending members").
//
// vota::CGeraDadosDinamicos, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.cpp:
// - StartState 11865 (slot 2, record :47, whose line stays blank there): fns 491, 6734 and 6737, with no name; its
//   other callees are named (vota::CEstadoAudio::GetInst, fn 509, an api::EUeAssertError throw, and
//   CVerificaHorarioZeresima::GetInst, fn 5947, unit 138).
//
// vota::CInicioVotacao, in src/uenux2/src/app/vota/eleitor/iniciovotacao/ciniciovotacao.cpp:
// - StartState 11988 (slot 2) and ProcessTick 11987 (slot 8): each calls fn 5972, not written, which calls fns 491 and
//   1269, with no name.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.h"
#include "app/vota/eleitor/iniciovotacao/ciniciovotacao.h"

namespace vota {

void CGeraDadosDinamicos::StartState()
{
    __builtin_trap();
}

void CInicioVotacao::StartState()
{
    __builtin_trap();
}

void CInicioVotacao::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
