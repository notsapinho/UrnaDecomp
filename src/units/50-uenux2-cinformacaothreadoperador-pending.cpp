// Pending members: the vota::impl::CInformacaoThreadOperador members
// src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp does not hold yet. Their bodies are NOT the
// target's, they trap, and the vtable that object emits names each of them. Defined in slot order, as the target's
// function order has them. The names are chosen (iinformacaothreadoperador.h says from what). Target functions, by
// vtable slot (vtable @1590108; ledger/vtables.json), and what each waits for:
//   16 10569  formats "{:04}" over a count: fn 1269 of comum::CRdvVota::GetInst() (fn 555) when fn 697 holds, else
//             CEleitores +104 (fn 326). Of those four it waits for fn 1269, which has no name; the symbol file names
//             its std::format code
//   17 10568  sets +12 from fn 5412, which has no body of ours
//   19 10566  returns false in the training phase (fn 1485, vota::EhTreinamento, matched from fragment 168), else
//             compares CDateTime::Now() (fn 479) with comum::CConfiguracaoEleicao's date at +580 and, when CEleitores'
//             word at +104 is not 0, with the last vote's time after operator+=(300) (fn 2233), which inlines
//             CEstadoGeralVota::GetDtHrUltimoVoto (record cestadogeralvota.h:131, the throw of code 8092 "Nenhum
//             eleitor votou"). Every callee has a name; it waits for three things no header has: that getter, inline
//             at line 131 of app/comum/dados/md/estadoaplicacao/cestadogeralvota.h, the api::CDateTime at +580 of
//             app/comum/dados/cconfiguracaoeleicao.h and an accessor of the word at +104 of app/comum/dados/celeitores.h
//   21 10564, 22  10563  m_identidadeDigitada = identidade; and m_tipoIdentidadeDigitada = tipo;, each then calling fn
//             2225: 757 B, reached from these two only, that fills +48 and +68 from the voter register and calls fns
//             1926, 2803, 566, 187, 326, 1703 and 708, which all match (566 is unit 178's, 2803 unit 110's), and holds
//             CEleitores's lookup of a voter by identity inlined: find (1703) in the map at +112 of CEleitores, which
//             celeitores.h declares with a std::string key, then CDataMap::Find on the value. No vtable slot holds
//             it, so it is no pending member. Against an import standing for it, 10563 differs in that call's operand
//             alone (try-tu --single). 10564's object has the target's calls, four of them to fn 2225, and its lone
//             score is noise: alone, binaryen inlines the string assigns
// Move each into cinformacaothreadoperador.cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/operador/comum/cinformacaothreadoperador.h"

namespace vota::impl {

std::string CInformacaoThreadOperador::GetTextoComparecimento() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::AgendaInspecao()
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::IsVotacaoBloqueadaPorHorario() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::SetIdentidadeDigitada(const std::string&)
{
    __builtin_trap();
}

void CInformacaoThreadOperador::SetTipoIdentidadeDigitada(ecourna::app::dados::ETipoIdentificadorEleitor)
{
    __builtin_trap();
}

} // namespace vota::impl
