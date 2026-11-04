// Pending members: the virtual member of comum::CGeradorBUQRCodeVota that
// src/uenux2/src/app/comum/relatorios/cgeradorbuqrcodevota.cpp does not hold yet. The class's vtable (emitted with its
// destructor, the key function, in that file's TU) needs it defined; this body is NOT the target's, it traps. It moves
// into the class when it is reconstructed; delete this file with it.
// - CGeradorBUQRCodeVota::Slot2, vtable slot 2, target fn 11242 (10017 B, no record of its own; it holds
//   CEstadoGeralVota::GetDtHrInicioAquisicao and GetDtHrFimAquisicao inlined, records cestadogeralvota.h:90 and 106). It
//   sets the QR code's header fields ("ORIG:{} " to "HREM:{} ") in the CCabecalhoQRCodeBuilder that Gera (fn 5604)
//   passes it, through setters binaryen inlines (its ORIG field is two frames, "RED" or "VOTA" on the flag at +418:
//   read, by GetCabecalho's ORLC in ccabecalhoqrcodebuilder.h, as two one-caller setters). Each of its direct callees
//   has a match or a name now: the last two, fns 1935 and 2821, CEleitores::QuantidadeHabilitacaoBiografica and
//   QuantidadeHabilitacaoBiometrica (unit 110), match, and so do 3752, comum::CLocal::GetAgregadas (unit 89), 1933,
//   comum::CLocal::GetLocalID (unit 89), 2841,
//   comum::CAppInfo::TemVota (unit 109), 2822, comum::CEleitores::QuantidadeHabilitacaoSemBiometria (unit 110), which
//   11242 calls on comum::CEleitores::GetInst()'s result (fn 326), and 2823, CEleitores::QuantidadeAptos (unit 110).
#include "app/comum/relatorios/cgeradorbuqrcodevota.h"

namespace comum {

void CGeradorBUQRCodeVota::Slot2(CCabecalhoQRCodeBuilder&) const
{
    __builtin_trap();
}

} // namespace comum
