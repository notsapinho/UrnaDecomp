// vota::CControladorRegistraMesariosVota's slots that are not written yet, and vota::CRegistroMesarioEncerrado's two. Each
// traps, so no match can land on it, and each moves into its class's .cpp when it is written. What each holds and waits
// for (the target's bodies, read with pnpm wasm fn):
// - slot 5, fn 10797: reads comum::CAppInfo::GetInst().GetVota().GetEstadoVota() and writes 55 for 54 and 58 for 57;
//   for 56 it writes 55 when fn 1269 on fn 555's result is false, +8 of fn 1391's result is 0 and +48 of
//   CAppInfo::GetGeral()'s (fn 291) is not 51; after a write it calls fn 491; waits for fns 491, 1269 and 1391;
// - slot 7, fn 10795: tests fn 3606's (states 55, 56) or fn 2727's (58) result on fn 815's for more than 5, else returns
//   true; waits for fn 815 and for 2727 and 3606, calls of fn 6007 with 2 and 1;
// - slot 9, fn 10794: returns what fn 5343 returns, vota::CAguardaInicio's GetInst (its vptr) with the constructor
//   inlined, 2105 B, which builds a form with api::CMTFormBuilder::AddTextField (fns 180 and 651); waits for fn 5343,
//   whose one callee with no name is fn 1694;
// - slots 13 and 14, fns 10790 and 10789: fn 2264 over comum::CEleitores (fn 326) and the titulo of slots 17 and 18, the
//   first as a bool; wait for fn 566, 2264's callee;
// - slot 16, fn 10786: calls fn 4662, which throws an api::CUeDesligandoError that fn 1685 builds when the byte at
//   1832936 is 1, and else calls fn 4657 (1048 B); waits for fns 4662, 1685 and 4657;
// - CRegistroMesarioEncerrado::ProcessKey, fn 10762: for key 12, stores fn 652's result at +4, the next state; waits for
//   fn 652.
#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"
#include "app/vota/eleitor/fimvotacao/cregistromesarioencerrado.h"

namespace vota {

void CControladorRegistraMesariosVota::Slot5() const
{
    __builtin_trap();
}

bool CControladorRegistraMesariosVota::Slot7() const
{
    __builtin_trap();
}

comum::CAppState& CControladorRegistraMesariosVota::Slot9() const
{
    __builtin_trap();
}

bool CControladorRegistraMesariosVota::Slot13() const
{
    __builtin_trap();
}

comum::md::CComparecimentoMesario* CControladorRegistraMesariosVota::Slot14() const
{
    __builtin_trap();
}

void CControladorRegistraMesariosVota::Slot16() const
{
    __builtin_trap();
}

void CRegistroMesarioEncerrado::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
