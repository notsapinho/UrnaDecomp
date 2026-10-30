// Pending members: the vota::impl::CInformacaoThreadOperador members
// src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp does not hold yet. Their bodies are NOT the
// target's, they trap, and the vtable that object emits names each of them. Defined in slot order, as the target's
// function order has them. The names are chosen (iinformacaothreadoperador.h says from what). Target functions, by
// vtable slot (vtable @1590108; ledger/vtables.json), and what each waits for: callees with no body of ours. Records
// name fns 326, 656, 555, 187, 903, 1926 and 566, so each of those wants its body and a symbol-file line; fns 697,
// 1269, 5412, 1485, 479, 759, 2233, 2225, 2803, 1703 and 185 have no record and no name yet either.
//   3  10580  +4, else asks comum::CEleitores::GetInst() (fn 326) and CDataMap<...>::GetCurrent (fn 656)
//   5  10579  the same question as slot 3 without +4 (fns 326, 656)
//   16 10569  formats "{:04}" over a count: fn 1269 of comum::CRdvVota::GetInst() (fn 555) when fn 697 holds, else
//             CEleitores +104 (fn 326). Those four are what it waits for: the symbol file names its std::format code
//   17 10568  sets +12 from fn 5412
//   19 10566  compares api::CDateTime values; inlines CEstadoGeralVota::GetDtHrUltimoVoto (record
//             cestadogeralvota.h:131, where its stub was) and calls fns 1485, 479, 187, 759, 326, 185, 903, 2233, 170
//   21 10564, 22  10563  m_identidadeDigitada = identidade; and m_tipoIdentidadeDigitada = tipo;, each then calling fn
//             2225: 757 B, reached from these two only, that fills +48 and +68 from the voter register and calls fns
//             1926, 2803, 566, 187, 326, 1703 and 708. No vtable slot holds it, so it is no pending member. Against an
//             import standing for it, 10563 differs in that call's operand alone (try-tu --single). 10564's object has
//             the target's calls, four of them to fn 2225, and its lone score is noise: alone, binaryen inlines the
//             string assigns
// Move each into cinformacaothreadoperador.cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/operador/comum/cinformacaothreadoperador.h"

namespace vota::impl {

bool CInformacaoThreadOperador::IsAudioAtivado() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::IsAudioAtivadoCadastro() const
{
    __builtin_trap();
}

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
