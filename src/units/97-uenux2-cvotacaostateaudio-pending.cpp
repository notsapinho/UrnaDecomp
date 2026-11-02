// Pending members of unit 97: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables.
//
// vota::CConfirmaVotoEmCargo, slot 9 (ProcessInputAudio 11754, record cvotacaostateaudio.cpp:209 of its inlined
// EmiteEcoCorrigeConfirma): it calls fn 1455 (CVotacaoStateAudio::PlayKey, written since) and fns 3229 and 4471
// (vota::CEleitorVotando's GetInst and RegistraVoto, unit 197), and reads vota::g_numeroDigitado
// (app/vota/eleitor/comum/cinformacaoeleitor.h): its callees are matched, and it is not written. ProcessInputAudio is
// the class's key function here, so this object emits its vtable, its typeinfo and nothing else of it; its real key
// function is not recorded.
// vota::CPedeProporcional, slot 9 (ProcessInputAudio 11711, record cpedeproporcional.cpp:84, 811 B), and
// vota::CPedeMajoritario's (ProcessInputAudio 11683, records cpedemajoritario.cpp:64 and :125, 1210 B): each calls slot
// 13 (fn 3139, CVotacaoStateAudio's, written since) and one more function, fn 5922 (no name) in 11711 and fn 4550
// (vota::CLogVota::LogaErroPartidoNaoEncontrado, unit 119) in 11683, and reads vota::g_numeroDigitado.
// vota::CCompletaProporcional, slots 9 and 13 (ProcessInputAudio 11756, 786 B, and EmiteEcoComInputField 5930, record
// ccompletaproporcional.cpp:60, 522 B): slot 9 calls slot 13 and reads vota::g_numeroDigitado; slot 13 is not read
// here. ProcessInputAudio is the class's
// key function here, as CConfirmaVotoEmCargo's is.
// vota::CMajoritarioValido::AoConcluirEntrada and vota::CConfirmaVotoNominal::AoConcluirEntrada (slot 17, one target
// body, fn 5925, 2141 B): it logs and runs a vota::impl::IPoliticaExecucaoEleitor through its GetInst, written in
// unit 165 with the has<T> and push<T> thunks it calls (2744, 5407), which match; every direct callee of 5925 is
// matched or named now (splat/matched.txt, splat/symbol_addrs.txt), and the member is not written.
// Its stub sat in app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp, where the record of the GetInst it holds inlined
// lies (:45); with these traps in the vtables the stub generator writes it no more.
//
// vota::IConfereVotoEmCargo, slots 9, 10 and 12 (ProcessInputAudio 11791, record cconferevotoemcargo.cpp:80, 71 B;
// StartStateAudio 11793, 333 B, which holds the record :41 of an anonymous-namespace GetCargoID; ProcessTickAudio
// 11790, 131 B): 11791's callees match (fn 1455, CVotacaoStateAudio::PlayKey, since it was written; fn 455,
// CPolySingleton<api::IInputKbd>::instance, since unit 237), and it is not written; 11790 waits for
// ExecutarAposAudioAtual (fn 3851, record :95, 781 B, not written) and the std::function it builds; 11793 is not read
// here. The class's key function is its destructor, in cconferevotoemcargo.cpp, so that object emits the vtable.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"
#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"
#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"
#include "app/vota/eleitor/votaproporcional/cconfirmavotonominal.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"

namespace vota {

void CConfirmaVotoEmCargo::ProcessInputAudio()
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
