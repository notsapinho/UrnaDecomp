// Pending members of unit 97: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables.
//
// vota::CVotacaoStateAudio, in src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:
// - StartState 7028 (slot 2), 55 B: sets +11 from fn 509's +4, calls slot 10 and registers the +13 tick. Its callees are
//   matched, 509 and 316 (the queue singleton fn 700 is called on) among them: it is only not written.
// - FinishState 7022 (slot 5), 132 B: cancels the wait, stops both ticks through fns 422 and 316, calls slot 11. It
//   waited for fn 422, CThreadVota::StopTick, which unit 02 matches now.
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
// vota::CConfirmaProporcional::GetProximoEstado (slot 16, fn 11751, a chosen name): it returns fn 3849, the
// vota::CPedeProporcional singleton, built by fn 6051, which has no name. It emits that class's vtable the same way.
// vota::CEstadoComDesligamentoAutomatico::ProcessTick (slot 8, fn 12061, record cestadocomdesligamentoautomatico.cpp:44 of
// its lambda): it waits for fns 5474 and 5979 (479, 759 and 1000, unit 125's, and vota::CLogVota::GetInst, fn 184, match).
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/votaproporcional/cconfirmaproporcional.h"

namespace vota {

void CVotacaoStateAudio::StartState()
{
    __builtin_trap();
}

void CVotacaoStateAudio::FinishState()
{
    __builtin_trap();
}

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

comum::CAppState* CConfirmaProporcional::GetProximoEstado() const
{
    __builtin_trap();
}

void CEstadoComDesligamentoAutomatico::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
