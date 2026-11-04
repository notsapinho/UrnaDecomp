// vota::CNomeEleitor::HabilitaEleitor (target fn 5400) and vota::EleitorNaFaixaSemBiometria (no target index). This
// comment is the reconstruction's: no record names this file or the functions. HabilitaEleitor's two target callers,
// CNomeEleitor's StartState and ProcessInput (cnomeeleitor.cpp's), keep the call where clang inlines it in their TU (cost
// 185, threshold 250), so it is in a TU of its own (docs/reference/facts/placing.md P2). EleitorNaFaixaSemBiometria's
// one caller, ProcessInput, holds its test as `i32.eqz(i32.and(gt_u, le_u))`, which clang turns into `i32.or(le_u,
// gt_u)` when it sees the whole expression (measured), so it is out of line here and binaryen inlined it, a reading. The
// file's name and path, and both functions' names, are chosen (src/units/239-uenux2-cnomeeleitor.mk).
#include "app/vota/operador/confirmaidentidade/cnomeeleitor.h"

#include "api/ipc/cmessagequeue.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

namespace vota {

void CNomeEleitor::HabilitaEleitor()
{
    LimpaBiometria();
    if (IsAudioAtivado()) {
        SetNextState(&CHabilitaAudioEleitor::GetInst());
    } else {
        CThreadEleitor::GetInst().GetMensagens().Post(1);
        SetNextState(&CMostraEleitorVotando::GetInst());
    }
}

bool EleitorNaFaixaSemBiometria()
{
    comum::CEleitores& eleitores = comum::CEleitores::GetInst();
    const size_t quantidade = eleitores.GetQuantidade();
    const int sequencial = eleitores.GetCurrent()->GetEleitor().GetSequencial();
    return sequencial > quantidade / 6 * 5 && sequencial <= quantidade;
}

} // namespace vota
