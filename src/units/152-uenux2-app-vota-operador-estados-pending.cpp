// Pending members of the classes of src/units/152-uenux2-app-vota-operador-estados.mk, each reached only through its
// vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move each into
// its class's .cpp when it is reconstructed, and delete this file with the last. What each waits for is a callee with
// no name, or fn 652, written and unresolved (unit 161) (ledger/callgraph.tsv against splat/symbol_addrs.txt).
// Fn 501, which six of them call too, matches now (api::CPriorityMessageQueue<api::SMessage>::Insert, named by its
// callers' calls: src/units/269-uenux2-cmessagequeue-insert.mk):
// - vota::CPerguntaEleitorVotando::ProcessInput (fn 10415, slot 7): every direct callee has a name now (1151 is unit
//   121's vota::AdicionaCampoNumerico, 1150 unit 142's); not written.
// - vota::CPerguntaFilaEleitorVazia::ProcessInput (fn 10713, slot 7): fn 3631, CPedeTituloEncerramento's GetInst,
//   which calls fn 1151.
// - vota::CHorarioVotacaoTerminou::ProcessInput (fn 10757, slot 7): a thunk into binaryen's fn 2295, with the slots 7 of
//   vota::CEleitorImpedidoJustificarVotoCPF (10604) and vota::CEncerramentoHorarioInvalido (10709); 2295 calls fn 652.
// - vota::CInspecionaUrna::ProcessInput (fn 11797, slot 7): fns 2380 and 6557.
#include "app/vota/eleitor/cinspecionaurna.h"
#include "app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"
#include "app/vota/operador/outrasopcoes/chorariovotacaoterminou.h"
#include "app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.h"

namespace vota {

void CPerguntaEleitorVotando::ProcessInput()
{
    __builtin_trap();
}

void CPerguntaFilaEleitorVazia::ProcessInput()
{
    __builtin_trap();
}

void CHorarioVotacaoTerminou::ProcessInput()
{
    __builtin_trap();
}

void CInspecionaUrna::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
