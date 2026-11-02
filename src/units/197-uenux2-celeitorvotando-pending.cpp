// Pending members: the vota::CEleitorVotando slots src/uenux2/src/app/vota/eleitor/celeitorvotando.cpp does not hold
// yet. The class's vtable is emitted with its destructor, the key function, in celeitorvotando.cpp's object, and it
// needs these too; their bodies are NOT the target's, they trap. Target functions, reached through the vtable:
// - StartState 7377 (slot 2, records celeitorvotando.cpp:125 and :131 of IniciaCiclo), 2313 B: it empties
//   vota::g_votosEleitor's vector in place and holds three functions of other files inlined by binaryen, each behind a
//   prologue of its own, none written: comum::CEleitores::GetCurrentAbrangenciaEleitor (record celeitores.cpp:497),
//   comum::CCargos::FiltraPorAbrangencia (record ccargos.cpp:249) and a sort of the positions with the comparator at
//   table slot 2357 (libc++'s introsort, fn 2837, with fns 2833 and 5804 under it, none written); and it calls fn 3721,
//   which has no name (its other callers, fns 2824 and 5761, are not written either);
// - NeedChangeState 7352 (slot 3, record :294), 305 B: calls comum::md::CVotos::Insere (fn 4454, record cvotos.cpp:40),
//   not written;
// - ProcessKey 7337 (slot 6), 96 B: calls suspenderEleitor (fn 4442, records :410 and :427), not written, which makes
//   RegistraVoto's calls and calls fn 4454 and DescartaVotos (fn 4449, records :253 and :254), not written, over fn 1091
//   (api::CPolySingleton<api::ISound>::instance), not matched.
// Move each into celeitorvotando.cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/celeitorvotando.h"

namespace vota {

void CEleitorVotando::StartState()
{
    __builtin_trap();
}

bool CEleitorVotando::NeedChangeState()
{
    __builtin_trap();
}

void CEleitorVotando::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
