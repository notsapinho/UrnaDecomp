#pragma once

#include <filesystem>
#include <string>

#include "api/gui/itext.h"
#include "ecourna/api/uetypes.hpp"

namespace api {
class CPaperFormBuilder;
}

// The free functions of app/vota/comum/votadefs.cpp that other files call. No record names this header, so its path is
// chosen, beside the .cpp, whose records name free functions of namespace vota. Only what a written function needs is
// declared.

namespace comum {

// The count of copies printed that GetQuantidadeMaximaBUsAdicionais returns: its record names the type,
// comum::TQtdImpresso, and the function returns it masked to a byte (fn 4582's `& 255`), so it is 8 bits wide and
// unsigned. No record names the header that declares it: it is declared here, beside its one user, a choice.
using TQtdImpresso = uebyte;

} // namespace comum

namespace vota {

// Target fns 3290 and 3288 (records votadefs.cpp:103 and 110): the signature check of a file of the work directory of
// the internal and the external flash, through comum::ValidarUE.
void VerificaAssinaturaMI(const std::string& arquivo);
void VerificaAssinaturaMV(const std::string& arquivo);

// Target fn 4625: the signature check of the vota files (vota.bin, rdv.dat, ze.dat, rze.dat, bu.dat, buj.dat, bim.dat)
// that exist in a directory, each against its package (vota.vsu, ...) through a comum::CPacoteArquivos of the urna's
// key and vota's application. Its one target caller, fn 7787, calls it twice, with comum::CPath::GetPathTrab (fn 358)
// of the internal and the external flash. No record, slot or string names it: its name, its parameter's type (a
// std::filesystem::path, which it copies to append to) and its being a free function of namespace vota are chosen, and
// its file is a reading of where its data lie (src/units/168-uenux2-app-helpers.mk).
void VerificaAssinaturaArquivos(const std::filesystem::path& diretorio);

// Target fn 4582 (record votadefs.cpp:135): how many more copies of the BU may be printed.
comum::TQtdImpresso GetQuantidadeMaximaBUsAdicionais();

// Target fns 1488 and 1487: the marker file "dinamico/imprimindo" under the internal flash's root
// (comum::CPath::GetPathRootSemSA(FLASH_INTERNA), fn 634), which a printing state opens around each printed file: 1488
// creates it empty (an api::CFile opened "wb" and closed) and 1487 removes it when it exists, each then calling
// api::CSynchronizer::GetInst().Sync() (fns 600, 620). Seven printing functions call both (2890, 11852, 11855, 11991,
// 12068, 12071, 12074). 1487 holds the existence test after a stack prologue of its own: a function binaryen inlined
// into its one caller (docs/reference/facts/reading.md R10), ExisteArquivoImprimindo. No record, slot or string names
// the three: their names, their being free functions of namespace vota (they read no state) and their file are chosen.
void CriaArquivoImprimindo();
bool ExisteArquivoImprimindo();
void RemoveArquivoImprimindo();

// Target fn 1485: whether the load is the training phase. Its name is chosen (no record, slot or string names it), after
// the tree's spelling of the same test (comum::CAppInfo::EhTreinamentoEleitor, CRelatorioTesteImpressora::EhTreinamento).
bool EhTreinamento();

// Target fn 1823: the training of the mesarios, the load's training phase (EhTreinamento, which clang holds inlined here,
// fn 1485 elsewhere) when the voters' training is off (CEstadoGeralVota's byte at +72, GetTreinamentoEleitor), the test
// RegistraMesarios writes in place. Its six callers (fns 7306, 10465, 10474, 10478, 10500, 10512), in five TUs, all keep
// the call. A reading of where it sits: EhTreinamento's code is inlined in it, which clang does in EhTreinamento's own
// TU, and in use band 6 it comes right before fn 1822 (CPolySingleton<IInterfaceSavd>::instance), the linkonce copy
// this object's VerificaAssinaturaMI is the first to mention in our link; so it is defined above that function. No
// record, slot or string names it: its name, its being a free function of namespace vota and its file are chosen.
bool EhTreinamentoMesario();

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

// Target fn 4578: whether the election takes no justification: the negation of comum::CInformacaoEleicao::
// AceitaJustificativa (fn 5918) on the urna's parameters. Two callers keep the call, in two TUs:
// vota::CProcuraEleitor::StartState (10631), which starts the justification of a voter it does not find only when this
// is false, and vota::CEleitorEncontrado::StartState (10635). No record, slot or string names it; its name, its being a free
// function and its file are chosen.
bool NaoAceitaJustificativa();

} // namespace vota
