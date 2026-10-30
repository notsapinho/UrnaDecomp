// Pending members: the vota::CProgressoEncerramento overriders
// src/uenux2/src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp does not hold yet. The class's vtable is
// emitted there with the destructor, its key function, and needs them defined; their bodies are NOT the target's, they
// trap. Target functions, all three reached only through the vtable (slots 2 to 4) and named by no record, symbol or
// caller (the names are chosen in app/comum/cabstracttelaprogresso.h):
// - Inicia 12103 (slot 2): under the mutex, sets the bar to its lower limit through fn 3667 (the bar's setter, which
//   clamps to the limits at +28/+32 and marks the form to redraw) and calls the form's slot 2;
// - Finaliza 12102 (slot 3): under the mutex, sets the bar to its upper limit through fn 3667;
// - Incrementa 12101 (slot 4): under the mutex, advances the bar through fn 5508.
// fns 3667 and 5508 are api::CProgressBar members that have no name yet. Move each into cprogressoencerramento.cpp when
// it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/fimvotacao/cprogressoencerramento.h"

namespace vota {

void CProgressoEncerramento::Inicia()
{
    __builtin_trap();
}

void CProgressoEncerramento::Finaliza()
{
    __builtin_trap();
}

void CProgressoEncerramento::Incrementa()
{
    __builtin_trap();
}

} // namespace vota
