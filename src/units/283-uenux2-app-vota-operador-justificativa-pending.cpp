// Fragment 283's members that are not written yet. Each traps, so no match can land on it, and each moves into its
// class's .cpp when it is written. What each holds and waits for (the target's bodies, read with pnpm wasm fn):
// - vota::CPedeAnoNascimento::ProcessInput, fn 10590 (slot 7, 4305 B): reads the year typed, and through its record
//   cjustificador.cpp:30 holds comum::CJustificador's justification inlined; it holds CAnoInformadoInvalido's and
//   CEleitorMenor16Anos's GetInst inlined, and calls CJustificativaEfetuada::GetInst (2747). It waits for fn 5725, a
//   callee with no name (ledger/callgraph.tsv against splat/symbol_addrs.txt).
// - vota::CEleitorImpedidoJustificarVotoCPF::ProcessInput, fn 10604 (slot 7): `f2295(p0, 5, 1589644)`, a thunk into the
//   body binaryen merged from five states' ProcessInput (fns 10461, 10604, 10667, 10709 and 10757, `pnpm wasm fn
//   ../target/vota_web_wasm.wasm 2295`), passing api::INPUT_CORRIGE and its TU's record of Read()
//   (cinteractiveform.h:57). The source, `if (m_form->Read() == api::INPUT_CORRIGE) { m_pNextState =
//   &CPedeIdentidade::GetInst(); }`, matches once our link forms that body: it waits for the other members of 2295.
#include "app/vota/operador/justificativa/celeitorimpedidojustificarvotocpf.h"
#include "app/vota/operador/justificativa/cpedeanonascimento.h"

namespace vota {

void CPedeAnoNascimento::ProcessInput()
{
    __builtin_trap();
}

void CEleitorImpedidoJustificarVotoCPF::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
