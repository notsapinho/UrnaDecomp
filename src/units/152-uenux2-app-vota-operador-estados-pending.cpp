// Pending members of the classes of src/units/152-uenux2-app-vota-operador-estados.mk, each reached only through its
// vtable. The classes' vtables need every slot defined; these bodies are NOT the target's, they trap. Move each into
// its class's .cpp when it is reconstructed, and delete this file with the last. What each waits for is a callee with
// no name (ledger/callgraph.tsv against splat/symbol_addrs.txt). Fn 501, which six of them call too, matches now
// (api::CPriorityMessageQueue<api::SMessage>::Insert, named by its callers' calls:
// src/units/269-uenux2-cmessagequeue-insert.mk):
// - vota::CSuspensaoAutomaticaEleitor::ProcessKey (fn 10404, slot 6): fn 652, one of the two states it goes to (the
//   other, fn 1150, is unit 142's CMostraEleitorVotando::GetInst).
// - vota::CPerguntaEleitorVotando::ProcessInput (fn 10415, slot 7): every direct callee has a name now (1151 is unit
//   121's vota::AdicionaCampoNumerico, 1150 unit 142's); not written.
// - vota::CDesabilitaAudioEleitor::ProcessInput (fn 10435, slot 7): fn 652 (it calls
//   CLogVota::LogaAudioDesativadoFimVotacao, fn 4529, written, and usleep, 3966, matched).
// - vota::CPerguntaFilaEleitorVazia::ProcessInput (fn 10713, slot 7): fn 3631, CPedeTituloEncerramento's GetInst,
//   which calls fn 1151.
// - vota::CHorarioVotacaoTerminou::ProcessInput (fn 10757, slot 7): a thunk into binaryen's fn 2295, with the slots 7 of
//   vota::CEleitorImpedidoJustificarVotoCPF (10604) and vota::CEncerramentoHorarioInvalido (10709); 2295 calls fn 652.
// - vota::CInspecionaUrna::ProcessInput (fn 11797, slot 7): fns 2380 and 6557.
#include "app/vota/eleitor/cinspecionaurna.h"
#include "app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.h"
#include "app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.h"
#include "app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"
#include "app/vota/operador/outrasopcoes/chorariovotacaoterminou.h"
#include "app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.h"

namespace vota {

void CSuspensaoAutomaticaEleitor::ProcessKey(uebyte)
{
    __builtin_trap();
}

void CPerguntaEleitorVotando::ProcessInput()
{
    __builtin_trap();
}

void CDesabilitaAudioEleitor::ProcessInput()
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
