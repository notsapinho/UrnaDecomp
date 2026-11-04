// Pending of unit 156: the slots of its states not reconstructed, with trapping bodies so that the vtables link.
// - vota::CMostraQRCodeCertificado::StartState (slot 2, fn 12040, 1932 B): it builds the screen through fns 502, 576,
//   653 and 2782, each matched now (653 since unit 120's AddLabeledInputControl); the body is not written.
#include "app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.h"

namespace vota {

void CMostraQRCodeCertificado::StartState()
{
    __builtin_trap();
}

} // namespace vota
