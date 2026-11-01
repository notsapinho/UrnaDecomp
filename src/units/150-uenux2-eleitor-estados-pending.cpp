// Pending members of unit 150: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables.
//
// vota::CConfirmaVotoSemCandidato, in src/uenux2/src/app/vota/eleitor/cconfirmavotosemcandidato.cpp:
// - ProcessInputAudio 7428 (slot 9), 278 B: calls GetTelaCargoAtual (fn 4483) and slot 13, and fns 3229 and 4471,
//   which have no name;
// - EmiteEcoComInputField 4477 (slot 13, record :77), 243 B: waits for api::CInteractiveForm::Read() (record
//   cinteractiveform.h:57), which this tree does not hold, and calls fn 1455 (CVotacaoStateAudio's, not written) and fn
//   455 (CPolySingleton<api::IInputKbd>::instance, named, its row `differs`).
// vota::CInstrucaoVotacaoAcessibilidade, in src/uenux2/src/app/vota/eleitor/cinstrucaovotacaoacessibilidade.cpp:
// - ProcessInputAudio 7248 (slot 9, records :54 to :60), 1315 B: waits for CInteractiveForm::Read() as 4477 does;
// - StartStateAudio 7242 (slot 10, records :129 and :131), 123 B: stores 7 at +4 of what fn 1091
//   (api::CPolySingleton<api::ISound>::instance) returns, calls slot 4 of what fn 2079
//   (api::CPolySingleton<api::ITextToSpeech>::instance) returns with 2, calls slot 2 of the form at +28 and sets the
//   next state to this one. Fns 1091 and 2079 have no name; unit 100 reads them as the executable TU's copies, which
//   get a name from the votes of two matched callers.
// vota::CVisualizarCandidatos, in src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.cpp:
// - StartState 11876 (slot 2, records :132 and :140), 927 B: calls fn 6569 twice, which has no name, and fn 455.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/cconfirmavotosemcandidato.h"
#include "app/vota/eleitor/cinstrucaovotacaoacessibilidade.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

namespace vota {

void CConfirmaVotoSemCandidato::ProcessInputAudio()
{
    __builtin_trap();
}

std::pair<api::EInputResult, std::string> CConfirmaVotoSemCandidato::EmiteEcoComInputField(const CFormInterativoTelaVota&) const
{
    __builtin_trap();
}

void CInstrucaoVotacaoAcessibilidade::ProcessInputAudio()
{
    __builtin_trap();
}

void CInstrucaoVotacaoAcessibilidade::StartStateAudio()
{
    __builtin_trap();
}

void CVisualizarCandidatos::StartState()
{
    __builtin_trap();
}

} // namespace vota
