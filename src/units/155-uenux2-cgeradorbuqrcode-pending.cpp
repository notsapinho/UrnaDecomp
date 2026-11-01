// Pending members: the virtual member of comum::CGeradorBUQRCodeVota that
// src/uenux2/src/app/comum/relatorios/cgeradorbuqrcodevota.cpp does not hold yet. The class's vtable (emitted with its
// destructor, the key function, in that file's TU) needs it defined; this body is NOT the target's, it traps. It moves
// into the class when it is reconstructed; delete this file with it.
// - CGeradorBUQRCodeVota::Slot2, vtable slot 2, target fn 11242 (10017 B, no record of its own; it holds
//   CEstadoGeralVota::GetDtHrInicioAquisicao and GetDtHrFimAquisicao inlined, records cestadogeralvota.h:90 and 106). It
//   builds the QR code's header fields ("ORIG:{} " to "HREM:{} ") from the election's state, and waits for its direct
//   callees that have neither a match nor a name (splat/scan.tsv `no-candidate`, no line in splat/symbol_addrs.txt):
//   fns 1933, 1935, 2821, 2822, 2823, 2841 and 3752.
#include "app/comum/relatorios/cgeradorbuqrcodevota.h"

namespace comum {

std::string CGeradorBUQRCodeVota::Slot2() const
{
    __builtin_trap();
}

} // namespace comum
