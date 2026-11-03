// Pending members of the classes of src/units/161-uenux2-app-vota-operador-identidade.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
// What each waits for is a callee with no body here (ledger/callgraph.tsv against splat/matched.txt and
// splat/symbol_addrs.txt); fn 652, which two of them call, matches now:
//
// - vota::CControlaReconhecimento::StartState (target fn 10512, slot 2, 514 B): it resets the class's statics and calls
//   fns 781, 1823 and 2740 (and 1393, which matches: unit 110's celeitores.cpp).
// - vota::CVerificaDadoEleitor::ProcessInput (target fn 10443, slot 7, 2761 B): it calls fns 652, 5396
//   (CRegistraDigitalOperador::GetInst, unit 221), 4661, 2097 and 5665, which has no body here (a voter's year of
//   birth, the first four characters of the string at +68 of the voter's record), and it holds
//   vota::CDadoEleitorNaoConfere's GetInst and constructor inlined (the one store of that vptr, 1592648) with its two
//   forms, and three CLogVota members this tree lacks.
// - vota::CDadoEleitorNaoConfere::ProcessInput (target fn 10447, slot 7): on CONFIRMA it goes to fn 652's state or,
//   with CControlaReconhecimento::AvancaVerificacao inlined (record ccontrolareconhecimento.cpp:176), to fn 2735's
//   (CVerificaDadoEleitor::GetInst); both match now, and AvancaVerificacao is not written.
// - vota::IEleitorImpedidoVotar::StartState (target fn 10625, slot 2 of the base and of its six derived classes): it
//   calls fn 3616.
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

void CControlaReconhecimento::StartState()
{
    __builtin_trap();
}

void CVerificaDadoEleitor::ProcessInput()
{
    __builtin_trap();
}

void CDadoEleitorNaoConfere::ProcessInput()
{
    __builtin_trap();
}

void IEleitorImpedidoVotar::StartState()
{
    __builtin_trap();
}

} // namespace vota
