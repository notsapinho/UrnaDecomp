// Pending members of the five classes of src/units/142-uenux2-app-vota-estados-448.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// - vota::CPedeAnoNascimentoSemBiometria::ProcessInput (target fn 10489, slot 7, 2040 B): it calls fns 395, 5399 and
//   5665, which have no name (ledger/callgraph.tsv against splat/symbol_addrs.txt), and 2097 and 4661 (unit 161's).
// - vota::CMostraEleitorVotando::StartState (target fn 10427, slot 2): it copies vota::CThreadOperador's string at +108
//   into +12's string, shows the form and calls fn 5903 on what fn 2284 returns; those two have no name.
// - vota::CMostraEleitorVotando::ProcessKey (target fn 10425, slot 6, 4809 B, records cmostraeleitorvotando.cpp:127 and
//   159): it calls 20 functions with no name, among them fn 1901.
// - vota::CPerguntaCodigoSuspensao::ProcessKey (target fn 10419, slot 6): on keys 2, 5 and 13 it goes to
//   vota::CEleitorVotouNaoVotou::GetInst() (fn 1901), vota::CMostraEleitorVotando::GetInst() (fn 1150) or
//   vota::CSincronismoOperador::GetInst() (fn 1897). It waits for the first two, which have no body.
// - vota::CPerguntaCodigoSuspensao::ProcessInput (target fn 10420, slot 7, 1917 B): it calls fns 1150 and 3623, which
//   have no name, 2798 and 2803 (units 178 and 110), 501 (api::CPriorityMessageQueue<api::SMessage>::Insert, unit 174),
//   4535 (unit 152's) and
//   1398 (comum::IEventosLog::logaAlerta, unit 111).
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.h"
#include "app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.h"

namespace vota {

void CPedeAnoNascimentoSemBiometria::ProcessInput()
{
    __builtin_trap();
}

void CMostraEleitorVotando::StartState()
{
    __builtin_trap();
}

void CMostraEleitorVotando::ProcessKey(uebyte)
{
    __builtin_trap();
}

void CPerguntaCodigoSuspensao::ProcessKey(uebyte)
{
    __builtin_trap();
}

void CPerguntaCodigoSuspensao::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
