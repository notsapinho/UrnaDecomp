// Pending members: the virtual members of comum::CRelatorioTesteImpressora that
// src/uenux2/src/app/comum/relatorios/crelatoriotesteimpressora.cpp does not hold yet. The class's vtable (emitted with
// EhTreinamento, its key function, in that TU) needs them defined; their bodies are NOT the target's, they trap. Each
// moves into the class's .cpp when it is reconstructed; delete this file with the last one.
// - GetConteudoQRCode, slot 5, fn 11200 (330 B): builds a vector of string pairs from the general state (fn 5636, 3903 B),
//   copies it (fn 1300), adds one tag of two by a switch on 1 (fn 5783) and turns it into the string (fn 5782, 2390 B).
//   It waits for 5636, 5782 and 5783, none named or written.
// - GetDadosLocal, slot 15, fn 11188 (3304 B), with ConverteTipoAlimentacao's record at line 173 of
//   crelatoriotesteimpressora.cpp inlined: not reconstructed; its callees 2816 and 5738 have no name (654, 1881 and
//   1933 match: units 98, 00 and 89)
//   (no match line and no line in splat/symbol_addrs.txt), and it calls std::string::append, fn 160 (ledger/callgraph.tsv),
//   which -O2 inlines and the tree's -O3 calls (docs/reference/facts/levels.md V3).
#include "app/comum/relatorios/crelatoriotesteimpressora.h"

namespace comum {

std::string CRelatorioTesteImpressora::GetConteudoQRCode() const
{
    __builtin_trap();
}

std::vector<std::string> CRelatorioTesteImpressora::GetDadosLocal() const
{
    __builtin_trap();
}

} // namespace comum
