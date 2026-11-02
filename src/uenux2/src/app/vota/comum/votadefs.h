#pragma once

#include "api/gui/itext.h"

namespace api {
class CPaperFormBuilder;
}

// The free functions of app/vota/comum/votadefs.cpp that other files call. No record names this header, so its path is
// chosen, beside the .cpp, whose records name free functions of namespace vota. Only what a written function needs is
// declared.

namespace vota {

// Target fn 1485: whether the load is the training phase. Its name is chosen (no record, slot or string names it), after
// the tree's spelling of the same test (comum::CAppInfo::EhTreinamentoEleitor, CRelatorioTesteImpressora::EhTreinamento).
bool EhTreinamento();

// Target fn 1387: a line of 38 '-' added to a report with IPaper's style 1, aligned as the caller says (11946 and 12110
// pass 0, 11908 and 12105 pass 2). Four vota states' slot 2 call it (11908, 11946, 12105, 12110). No record names
// it; its name, its being a free function and its file are chosen.
void AdicionaSeparador(api::CPaperFormBuilder& builder, api::ETextAlignment alinhamento);

// Target fn 2520: whether the urna registers its mesarios now: comum::CInformacaoEleicao::ImprimeBJust (fn 1950, which
// reads CParametrosUrna's registrarMesarios) and not the voters' training (the test of
// comum::CAppInfo::EhTreinamentoEleitor, written in place: the target calls fn 185 twice and not fn 697). Four callers
// keep the call: vota::CDefineRotaPosReinicio::NeedChangeState (11858), which then goes to
// vota::CReinicioComparecimentoMesario, vota::CFimAquisicaoVotos::StartState (10737), vota::CQuerReimprimirZeresima's
// ProcessInput (11848) and vota::CEscolheOpcao::GetInst (2753). No record names it; its name, its being a free function
// and its file are chosen.
bool RegistraMesarios();

// Whether ze.dat is in the internal flash's work directory: api::CSystem::ExistFile (fn 412) on
// comum::CPath::GetPathTrab(FLASH_INTERNA) / "ze.dat". vota::CReinicioVotacao::StartState (fn 11835) holds it inlined
// behind a stack prologue of its own (docs/reference/facts/reading.md R10), so it is out of line in a TU other than its
// caller's and has no target index. Its name, its being a free function and its file are chosen.
bool ExisteArquivoZeresima();

} // namespace vota
