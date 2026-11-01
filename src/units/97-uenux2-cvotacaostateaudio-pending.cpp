// Pending members of unit 97: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables.
//
// vota::CVotacaoStateAudio, in src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:
// - ProcessInput 7029 (slot 7, record :69), 282 B, and ProcessTick 7010 (slot 8, records :120 and :388), 683 B: both
//   wait for fn 1091 (and waited for 422); 7010 holds IniciarEsperaFimAudio and its two lambdas (the __func vtables
//   @1536140 and @1536204), and calls PlayInterruptibleMessage (fn 3143).
// - EmiteEcoComInputField 3139 (slot 13, record :188), 525 B: waits for api::CInteractiveForm::Read() (record
//   cinteractiveform.h:57), which this tree does not hold, and for a definition of api::EInputResult.
// - FormataMensagem 6999 (slot 14, a chosen name), 4946 B: fills the {cargo-atual}-style tags; waits for the tags' sources.
// vota::CConfirmaVotoEmCargo, slot 9 (ProcessInputAudio 11754, record cvotacaostateaudio.cpp:209 of its inlined
// EmiteEcoCorrigeConfirma): it calls fns 1455, 3229 and 4471, which have no name, and reads the std::string at 1833288
// that no symbol names (exit destructor fn 13593). ProcessInputAudio is the class's
// key function here, so this object emits its vtable, its typeinfo and nothing else of it; its real key function is not
// recorded.
// vota::CEstadoComDesligamentoAutomatico::ProcessTick (slot 8, fn 12061, record cestadocomdesligamentoautomatico.cpp:44 of
// its lambda): it waits for fn 5474, not written, and fn 5979, vota::CExibeAlertaDesligamento::GetInst, not written
// (ctelasvota.h has the accessor of the +44 member it copies); 479, 759 and 1000, unit 125's, and
// vota::CLogVota::GetInst, fn 184, match.
// vota::CPedeProporcional, slot 9 (ProcessInputAudio 11711, record cpedeproporcional.cpp:84, 811 B), and
// vota::CPedeMajoritario's (ProcessInputAudio 11683, records cpedemajoritario.cpp:64 and :125, 1210 B): each calls slot
// 13 (fn 3139, pending above) and a function with no name (fn 5922 and fn 4550), and reads the std::string at 1833288.
// vota::CCompletaProporcional, slots 9 and 13 (ProcessInputAudio 11756, 786 B, and EmiteEcoComInputField 5930, record
// ccompletaproporcional.cpp:60, 522 B): slot 9 calls slot 13 and reads the std::string at 1833288; slot 13 is not read
// here. ProcessInputAudio is the class's
// key function here, as CConfirmaVotoEmCargo's is.
// vota::CPedeNulo::GetProximoEstado and vota::CPedeNominal::GetProximoEstado (slot 16, fns 11744, record cpedenulo.cpp:44,
// 433 B, and 11724, 495 B): every callee is matched or named (fn 1273 is CCandidaturas::Busca, unit 89's), and both
// assign the number typed to the std::string at 1833288, which no symbol names and no record places: its readers are
// these two, the four ProcessInputAudio above, CVotacaoStateAudio::FormataMensagem (6999) and vota::CEleitorVotando's
// fns 7377, 4459 and 5500, and its exit destructor is fn 13593. They wait for that object's declaration.
// vota::CMajoritarioValido::AoConcluirEntrada and vota::CConfirmaVotoNominal::AoConcluirEntrada (slot 17, one target
// body, fn 5925, 2141 B): it logs and runs a vota::impl::IPoliticaExecucaoEleitor through fn 5407, which has no name.
// Its stub sat in app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp, where the record of the GetInst it holds inlined
// lies (:45); with these traps in the vtables the stub generator writes it no more.
//
// vota::IConfereVotoEmCargo, slots 9, 10 and 12 (ProcessInputAudio 11791, record cconferevotoemcargo.cpp:80, 71 B;
// StartStateAudio 11793, 333 B, which holds the record :41 of an anonymous-namespace GetCargoID; ProcessTickAudio 11790,
// 131 B): 11791 waits for fn 455, CPolySingleton<api::IInputKbd>::instance, which has no name, and fn 1455
// (CVotacaoStateAudio's, not written); 11790 for ExecutarAposAudioAtual (fn 3851, record :95, 781 B, not written) and the
// std::function it builds; 11793 is not read here. The class's key function is its destructor, in
// cconferevotoemcargo.cpp, so that object emits the vtable.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"
#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"
#include "app/vota/eleitor/votaproporcional/cconfirmavotonominal.h"
#include "app/vota/eleitor/votaproporcional/cpedenominal.h"
#include "app/vota/eleitor/votaproporcional/cpedenulo.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"

namespace vota {

void CVotacaoStateAudio::ProcessInput()
{
    __builtin_trap();
}

void CVotacaoStateAudio::ProcessTick(uebyte)
{
    __builtin_trap();
}

std::pair<api::EInputResult, std::string> CVotacaoStateAudio::EmiteEcoComInputField(const CFormInterativoTelaVota&) const
{
    __builtin_trap();
}

std::string CVotacaoStateAudio::FormataMensagem(const std::string&) const
{
    __builtin_trap();
}

void CConfirmaVotoEmCargo::ProcessInputAudio()
{
    __builtin_trap();
}

void CEstadoComDesligamentoAutomatico::ProcessTick(uebyte)
{
    __builtin_trap();
}

void CPedeProporcional::ProcessInputAudio()
{
    __builtin_trap();
}

void CPedeMajoritario::ProcessInputAudio()
{
    __builtin_trap();
}

void CCompletaProporcional::ProcessInputAudio()
{
    __builtin_trap();
}

std::pair<api::EInputResult, std::string> CCompletaProporcional::EmiteEcoComInputField(const CFormInterativoTelaVota&) const
{
    __builtin_trap();
}

comum::CAppState* CPedeNulo::GetProximoEstado(const std::string&) const
{
    __builtin_trap();
}

comum::CAppState* CPedeNominal::GetProximoEstado(const std::string&) const
{
    __builtin_trap();
}

void CMajoritarioValido::AoConcluirEntrada(api::EInputResult)
{
    __builtin_trap();
}

void CConfirmaVotoNominal::AoConcluirEntrada(api::EInputResult)
{
    __builtin_trap();
}

void IConfereVotoEmCargo::ProcessInputAudio()
{
    __builtin_trap();
}

void IConfereVotoEmCargo::StartStateAudio()
{
    __builtin_trap();
}

void IConfereVotoEmCargo::ProcessTickAudio(uebyte)
{
    __builtin_trap();
}

} // namespace vota
