// Roots of src/units/161-uenux2-app-vota-operador-identidade.mk: the second call sites of the static members and
// CLogVota members whose target callers are not reconstructed yet.
//
// - The vtables: vota::CDadoEleitorNaoConfere's and vota::CInformaAnoNascimentoErrado's constructors are in the link,
//   inlined with their GetInst into fn 10443 (vota::CVerificaDadoEleitor::ProcessInput, this unit's) and fn 10489
//   (vota::CPedeAnoNascimentoSemBiometria::ProcessInput, unit 142's file), so no sink keeps those two vtables.
//   vota::CControlaReconhecimento's constructor is in the link, inlined into its GetInst (fn 1256), which
//   vota::CDigitalNaoReconhecidaPorTempo::StartState (10486, unit 282's) calls, so no sink keeps that vtable.
//   vota::CVerificaDadoEleitor's constructor is in the link, inlined into its GetInst (fn 2735), so no sink keeps that
//   vtable. vota::CEleitorNaoEncontrado's constructor is in the link, inlined into its GetInst (fn 5424), which
//   vota::CProcuraEleitor::StartState (10631) and CEleitorEncontrado::StartState (10635, both unit 104's) call, and
//   CEleitorJaVotou's, inlined into its GetInst, which 10635 holds (its file is unit 104's now), so no sink keeps those
//   two vtables; vota::IEleitorImpedidoVotar's comes with its constructor (fn 1905), which 5424 calls. CPedeIdentidade's
//   constructor is in the link, inlined into its GetInst (fn 652), and so is CIdentidadeInvalida's, inlined into its
//   GetInst, which vota::CValidaIdentidade::StartState (10627, unit 278's) holds.
// - The functions below have direct callers in the target, two call sites or more each (ledger/callgraph.tsv), so
//   binaryen keeps them out of line; the stand-ins give them those call sites, each standing for the callers it names:
//   CLogVota::LogaHabilitacaoCanceladaCapturaDigitalMesario (4522: 10451; 10452 is in the link), CPedeIdentidade::GetInst (652: 22 target callers, of which CEleitorVotouNaoVotou::ProcessInput,
//   10430, and the ones the stand-in's comment names are in the link). A stand-in goes when the target callers it names
//   are in splat/matched.txt or written in the link.
// - vota::CControlaReconhecimento::GetInst (fn 1256): its target callers are 10425, 10474, 10486 and 10500; 10474 and
//   10486 (unit 282's) are in the link and drop the result, as 10425 does, while 10500 (unit 239's, in the link) stores
//   it as its next state. The stand-in stands for 10425 and drops the result, as 10425 does: its read of the result
//   stood for 10500, a real reader in the link now, so it went (src/units/README.md "Companion files"), measured with
//   steps 6 to 10: every match row stays, 1256's among them.
// The call of CLogVota::LogaHabilitacaoCanceladaConfirmacaoDado (2097) went: its target callers 10500, 10443, 10447,
// 10489 and 10626 are in the link.
// The stand-in for vota::MontaTelaEleitorPodeVotar (5410) went: its callers 1256 (this unit's) and 5399 (unit 282's) are
// in the link.
// The stand-ins for AtingiuLimiteVerificacoes (5404), AtingiuLimiteTentativas and AvancaTentativa (5405, 5406) went:
// their callers 10447 and 10448 (unit 161) and 10473 and 10485 (unit 282) are in the link.
// The stand-in for CControlaReconhecimento::PrimeiraTentativa (5403) went: its one target caller, 10465 (unit 282's),
// which calls it twice, is in the link.
// The stand-ins differ in their bytes, from each other and from every target function. Compiled with APP_CXXFLAGS.
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

extern "C" {
int w161_pede_identidade() __asm__("_ZN4vota15CPedeIdentidade7GetInstEv");
}

namespace {

using vota::CControlaReconhecimento;
using vota::CLogVota;

// Stands for 10451.
__attribute__((noinline)) int CancelaUm()
{
    CLogVota& log = CLogVota::GetInst();
    log.LogaHabilitacaoCanceladaCapturaDigitalMesario();
    return 71;
}

// Stands for CPedeIdentidade::GetInst's (fn 652) other target caller, 10209 (in the link: 10590, unit 283's; 10443,
// unit 161's; 10689, unit 277's list's CEscolheOpcao::ProcessInput; 10447, unit 161's; 2295, the body binaryen merges from the five
// states' slot 7, 10452 and 10626, units 161, 221, 278, 283 and 277; 10217, 10404, 10435, 10527, 10646 and 10762, units
// 165, 152, 152, 281, 104 and 119; 10588 and 10624, units 174's and 161's; and 10718, 10721, 10731, 10734 and 10751,
// unit 277's).
__attribute__((noinline)) int PedeIdentidade()
{
    return w161_pede_identidade() + 89;
}

// Stands for 10425, which drops the result.
__attribute__((noinline)) int ControlaReconhecimento()
{
    CControlaReconhecimento::GetInst();
    return 161;
}

const void* volatile w161_sink;

struct SW161Roots {
    SW161Roots()
    {
        w161_sink = reinterpret_cast<const void*>(&CancelaUm);
        w161_sink = reinterpret_cast<const void*>(&PedeIdentidade);
        w161_sink = reinterpret_cast<const void*>(&ControlaReconhecimento);
    }
} w161_roots;

} // namespace
