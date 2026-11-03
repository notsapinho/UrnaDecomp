// Pending members of the five classes of src/units/142-uenux2-app-vota-estados-448.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CPedeAnoNascimentoSemBiometria::ProcessInput (target fn 10489, slot 7, 2040 B): it calls fns 5399 and 5665,
//   which have no name (ledger/callgraph.tsv against splat/symbol_addrs.txt), 395 (unit 31's), 2097 and 4661 (161's).
// - vota::CMostraEleitorVotando::ProcessKey (target fn 10425, slot 6, 4809 B, records cmostraeleitorvotando.cpp:127 and
//   159, SalvaHabilitacaoEleitor's): of its 46 distinct callees (ledger/callgraph.tsv), 14 have no name in
//   splat/symbol_addrs.txt or splat/matched.txt (fn 1901, unit 71's, matches now). It calls comum::CEleitorDadosHabilitacao's
//   constructor (2733), which cmostraeleitorvotando.cpp holds, four times: the roots file stands in for those calls.
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.h"

namespace vota {

void CPedeAnoNascimentoSemBiometria::ProcessInput()
{
    __builtin_trap();
}

void CMostraEleitorVotando::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
