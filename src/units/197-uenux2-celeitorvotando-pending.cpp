// Pending members: the vota::CEleitorVotando slot src/uenux2/src/app/vota/eleitor/celeitorvotando.cpp does not hold
// yet. The class's vtable is emitted with its destructor, the key function, in celeitorvotando.cpp's object, and it
// needs this one too; its body is NOT the target's, it traps. Target function, reached through the vtable:
// - ProcessKey 7337 (slot 6), 96 B: calls suspenderEleitor (fn 4442, records :410 and :427), not written, which makes
//   RegistraVoto's calls, calls FinalizaEleitor (fn 4454, written) and DescartaVotos (fn 4449, records :253 and :254),
//   not written, over fn 1091 (api::CPolySingleton<api::ISound>::instance, the executable TU's copy, which our link
//   holds only inlined into unit 170's votaSetAudioEnabled; that fragment says what 1091 waits for), not matched.
// Move it into celeitorvotando.cpp when it is reconstructed, and delete this file then.
#include "app/vota/eleitor/celeitorvotando.h"

namespace vota {

void CEleitorVotando::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
