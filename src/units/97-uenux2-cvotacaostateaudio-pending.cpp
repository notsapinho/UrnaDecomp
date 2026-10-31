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
// vota::CConfirmaVotoEmCargo, slots 9 and 10 (ProcessInputAudio 11754, record cvotacaostateaudio.cpp:209 of its inlined
// EmiteEcoCorrigeConfirma, and StartStateAudio 11755): they wait for GetTelaCargoAtual (fn 5928, record
// cconfirmavotoemcargo.cpp:71), which calls fn 3921, and for CInteractiveForm's members. ProcessInputAudio is the class's
// key function here, so this object emits its vtable, its typeinfo and nothing else of it; its real key function is not
// recorded.
// vota::CEstadoComDesligamentoAutomatico::ProcessTick (slot 8, fn 12061, record cestadocomdesligamentoautomatico.cpp:44 of
// its lambda): it waits for fn 5474, not written, and fn 5979, vota::CExibeAlertaDesligamento::GetInst, which waits for
// a way to vota::CTelasVota's +44 member (cexibealertadesligamento.h); 479, 759 and 1000, unit 125's, and
// vota::CLogVota::GetInst, fn 184, match.
// vota::CPedeProporcional, slots 9 and 10 (ProcessInputAudio 11711, record cpedeproporcional.cpp:84, 811 B, and
// StartStateAudio 11712, 103 B), and vota::CPedeMajoritario's (ProcessInputAudio 11683, records cpedemajoritario.cpp:64
// and :125, 1210 B, and StartStateAudio 11684, 103 B): each calls its class's GetTelaCargoAtual (fns 5923 and 5920,
// records :42 and :44), a thunk into fn 6050, which has no name, and the form's members.
// vota::CCompletaProporcional, slots 9, 10 and 13 (ProcessInputAudio 11756, 786 B, StartStateAudio 11757, 267 B, and
// EmiteEcoComInputField 5930, record ccompletaproporcional.cpp:60, 522 B): slots 9 and 10 call GetTelaCargoAtual (fn
// 5931, record :83), which calls fn 3921, which has no name; slot 13 is not read here. ProcessInputAudio is the class's
// key function here, as CConfirmaVotoEmCargo's is.
// vota::CPedeNulo::GetProximoEstado and vota::CPedeNominal::GetProximoEstado (slot 16, fns 11744, record cpedenulo.cpp:44,
// 433 B, and 11724, 495 B): both call fn 1273 (116 B), which has no name.
// vota::CMajoritarioValido::AoConcluirEntrada and vota::CConfirmaVotoNominal::AoConcluirEntrada (slot 17, one target
// body, fn 5925, 2141 B): it logs and runs a vota::impl::IPoliticaExecucaoEleitor through fn 5407, which has no name.
// Its stub sat in app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp, where the record of the GetInst it holds inlined
// lies (:45); with these traps in the vtables the stub generator writes it no more.
//
// vota::IConfereVotoEmCargo, slots 9, 10 and 12 (ProcessInputAudio 11791, record cconferevotoemcargo.cpp:80, 71 B;
// StartStateAudio 11793, 333 B, which holds the record :41 of an anonymous-namespace GetCargoID; ProcessTickAudio 11790,
// 131 B): 11791 waits for fn 455, CPolySingleton<api::IInputKbd>::instance, which has no name, and fn 1455
// (CVotacaoStateAudio's, not written); 11790 for ExecutarAposAudioAtual (fn 3851, record :95, 781 B, not written) and the
// std::function it builds; 11793 is not read here. ProcessInputAudio is the class's key function here.
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

void CConfirmaVotoEmCargo::StartStateAudio()
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

void CPedeProporcional::StartStateAudio()
{
    __builtin_trap();
}

void CPedeMajoritario::ProcessInputAudio()
{
    __builtin_trap();
}

void CPedeMajoritario::StartStateAudio()
{
    __builtin_trap();
}

void CCompletaProporcional::ProcessInputAudio()
{
    __builtin_trap();
}

void CCompletaProporcional::StartStateAudio()
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
