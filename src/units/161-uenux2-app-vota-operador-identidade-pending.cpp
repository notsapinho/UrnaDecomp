// Pending members of the classes of src/units/161-uenux2-app-vota-operador-identidade.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
// What each waits for is a callee with no body here (ledger/callgraph.tsv against splat/matched.txt and
// splat/symbol_addrs.txt):
//
// - vota::CControlaReconhecimento::StartState (target fn 10512, slot 2, 514 B): it resets the class's statics and calls
//   fns 781, 1393, 1823 and 2740.
// - vota::CControlaReconhecimento::ProcessInput (target fn 10511, slot 7): through Read() (record cinteractiveform.h:57
//   @1591088), on CONFIRMA it calls fn 3621 and goes to the state fn 2743 returns or, as fn 2746 decides (3621 and 2746:
//   unit 50), after a call of fn 501 (api::CPriorityMessageQueue<api::SMessage>::Insert, unit 174), to fn 1150's.
// - vota::CIdentidadeInvalida::ProcessInput (target fn 10667, slot 7): a thunk that passes INPUT_CORRIGE (5) and its
//   record (cinteractiveform.h:57 @1588432) to binaryen's fn 2295, whose next state is fn 652's.
// - vota::CVerificaDadoEleitor::ProcessInput (target fn 10443, slot 7, 2761 B): it calls fns 395, 652, 5396 and 5665.
// - vota::CDadoEleitorNaoConfere::ProcessInput (target fn 10447, slot 7): on CONFIRMA it goes to fn 652's state or,
//   with CControlaReconhecimento::AvancaVerificacao inlined (record ccontrolareconhecimento.cpp:176), to fn 2735's.
// - vota::CPedeIdentidade::StartState (target fn 10680, slot 2, records cpedeidentidade.cpp:62 and :63): it calls fns
//   2284 and 5903, 599 and 2226 (unit 50) and 1485 (vota::EhTreinamento, fragment 168).
// - vota::CPedeIdentidade::ProcessInput (target fn 10677, slot 7): it calls fns 2749, 2753, 5401 and 5430, and 2226,
//   3619 and 5414 (unit 50).
// - vota::CPedeIdentidade::ProcessTick (target fn 10676, slot 8): it calls fns 599, 2226 and 3620 (unit 50) and 501
//   (unit 174), so no callee of it waits now: it is not written yet.
// - vota::IEleitorImpedidoVotar::StartState (target fn 10625, slot 2 of the base and of its six derived classes): it
//   calls fn 3616.
// - vota::IEleitorImpedidoVotar::ProcessInput (target fn 10624, slot 7 of the same seven vtables): through Read()
//   (record cinteractiveform.h:57 @1589236) it goes to fn 652's state.
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/cidentidadeinvalida.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

void CControlaReconhecimento::StartState()
{
    __builtin_trap();
}

void CControlaReconhecimento::ProcessInput()
{
    __builtin_trap();
}

void CIdentidadeInvalida::ProcessInput()
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

void CPedeIdentidade::StartState()
{
    __builtin_trap();
}

void CPedeIdentidade::ProcessInput()
{
    __builtin_trap();
}

void CPedeIdentidade::ProcessTick(uebyte)
{
    __builtin_trap();
}

void IEleitorImpedidoVotar::StartState()
{
    __builtin_trap();
}

void IEleitorImpedidoVotar::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
