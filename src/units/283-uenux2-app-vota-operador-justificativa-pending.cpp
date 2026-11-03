// Fragment 283's members that are not written yet. Each traps, so no match can land on it, and each moves into its
// class's .cpp when it is written. What each holds and waits for (the target's bodies, read with pnpm wasm fn):
// - vota::CPedeAnoNascimento::ProcessInput, fn 10590 (slot 7, 4305 B): reads the year typed, and through its records
//   cjustificador.cpp:55 and :83 holds comum::CJustificador's justification inlined; it holds CAnoInformadoInvalido's
//   and
//   CEleitorMenor16Anos's GetInst inlined, and calls CJustificativaEfetuada::GetInst (2747). It waits for fn 5725, a
//   callee with no name (ledger/callgraph.tsv against splat/symbol_addrs.txt).
#include "app/vota/operador/justificativa/cpedeanonascimento.h"

namespace vota {

void CPedeAnoNascimento::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
