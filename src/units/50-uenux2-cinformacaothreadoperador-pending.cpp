// Pending members: the vota::impl::CInformacaoThreadOperador members
// src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp does not hold yet. Their bodies are NOT the
// target's, they trap, and the vtable that object emits names each of them. Defined in slot order, as the target's
// function order has them. The names are chosen (iinformacaothreadoperador.h says from what). Target functions, by
// vtable slot (vtable @1590108; ledger/vtables.json), and what each waits for:
//   16 10569  formats "{:04}" over a count: fn 1269 of comum::CRdvVota::GetInst() (fn 555) when fn 697 holds, else
//             CEleitores +104 (fn 326). Of those four it waits for fn 1269, which has no name; the symbol file names
//             its std::format code
//   19 10566  returns false in the training phase (fn 1485, vota::EhTreinamento, matched from fragment 168), else
//             compares CDateTime::Now() (fn 479) with comum::CConfiguracaoEleicao's date at +580 and, when CEleitores'
//             word at +104 is not 0, with the last vote's time after operator+=(300) (fn 2233), which inlines
//             CEstadoGeralVota::GetDtHrUltimoVoto (record cestadogeralvota.h:131, the throw of code 8092 "Nenhum
//             eleitor votou"). Every callee has a name; it waits for three things no header has: that getter, inline
//             at line 131 of app/comum/dados/md/estadoaplicacao/cestadogeralvota.h, the api::CDateTime at +580 of
//             app/comum/dados/cconfiguracaoeleicao.h and an accessor of the word at +104 of app/comum/dados/celeitores.h
// Move each into cinformacaothreadoperador.cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/operador/comum/cinformacaothreadoperador.h"

namespace vota::impl {

std::string CInformacaoThreadOperador::GetTextoComparecimento() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::IsVotacaoBloqueadaPorHorario() const
{
    __builtin_trap();
}

} // namespace vota::impl
