// vota::CControladorRegistraMesariosVota's slots that are not written yet. Each traps, so no match can land on it, and
// each moves into ccontroladorregistramesariosvota.cpp when it is written. What each holds and waits for (the target's
// bodies, read with pnpm wasm fn):
// - slot 5, fn 10797: reads comum::CAppInfo::GetInst().GetVota()'s first word (the vote state), writes 55 or 58 there and
//   calls fn 491; waits for fns 491, 1269 and 1391, and for a getter of the state and EEstadoVota's enumerators;
// - slot 6, fn 10796: maps the vote state 55, 56, 57, 58 to 1, 2, 0, 3 (a table at 534720), else 0; waits for the same
//   getter and enumerators;
// - slot 7, fn 10795: compares fn 3606's or fn 2727's result on fn 815's with 5 by the vote state; waits for fns 815, 2727
//   and 3606;
// - slot 9, fn 10794: returns what fn 5343 (2105 B, not written) returns; waits for fn 5343;
// - slots 10 and 15, fns 10792 and 10787: fn 6018 with 11 and 7, which passes +36 of vota::CThreadEleitor (fn 316), the
//   value as 16 bits in a frame slot, and 1 to fn 501; wait for fn 501;
// - slot 11, fn 10793: vota::CRegistroMesarioEncerrado's GetInst, inlined (a 12-byte comum::CAppState(1) whose vptr is
//   1586776, .bss pointer 1904888 and mutex 1904864); waits for that class;
// - slots 13 and 14, fns 10790 and 10789: fn 2264 over comum::CEleitores (fn 326) and the titulo of slots 17 and 18, the
//   first as a bool; wait for fn 566, 2264's callee;
// - slot 16, fn 10786: calls fn 4662; waits for fn 4662;
// - slot 28, fn 10774: CLogVota::GetInst() and fn 1398 (api::CLoga::loga of +4 with severity 2, not written) over
//   std::format("Limite de mesarios registrados atingido. Limite maximo: {}", 6u) (the literal has its accents); waits for
//   fn 1398, and for the level: the literal is 58 bytes and the target has no search of it for a brace, which -O2 keeps
//   past 36 bytes (docs/reference/facts/reading.md R13).
#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"

namespace vota {

void CControladorRegistraMesariosVota::Slot5()
{
    __builtin_trap();
}

int CControladorRegistraMesariosVota::Slot6()
{
    __builtin_trap();
}

bool CControladorRegistraMesariosVota::Slot7()
{
    __builtin_trap();
}

comum::CAppState& CControladorRegistraMesariosVota::Slot9()
{
    __builtin_trap();
}

void CControladorRegistraMesariosVota::Slot10()
{
    __builtin_trap();
}

comum::CAppState& CControladorRegistraMesariosVota::Slot11()
{
    __builtin_trap();
}

bool CControladorRegistraMesariosVota::Slot13()
{
    __builtin_trap();
}

comum::md::CComparecimentoMesario* CControladorRegistraMesariosVota::Slot14()
{
    __builtin_trap();
}

void CControladorRegistraMesariosVota::Slot15()
{
    __builtin_trap();
}

void CControladorRegistraMesariosVota::Slot16()
{
    __builtin_trap();
}

void CControladorRegistraMesariosVota::LogaLimiteMesariosAtingido()
{
    __builtin_trap();
}

} // namespace vota
