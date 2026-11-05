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
//   CLogVota::LogaHabilitacaoCanceladaCapturaDigitalMesario (4522: 10451; 10452 is in the link). A stand-in goes when
//   the target callers it names are in splat/matched.txt or written in the link. CPedeIdentidade::GetInst (652) needs
//   none: its last target caller that was not in the link, 10209 (CSincronismoOperador::ProcessKey, unit 104), is.
// - vota::CControlaReconhecimento::GetInst (fn 1256) needs none now: its target callers 10425 (unit 142's), 10474 and
//   10486 (unit 282's), which drop the result, and 10500 (unit 239's), which stores it as its next state, are in the
//   link, and the stand-in for 10425 went with it.
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

namespace {

using vota::CLogVota;

// Stands for 10451.
__attribute__((noinline)) int CancelaUm()
{
    CLogVota& log = CLogVota::GetInst();
    log.LogaHabilitacaoCanceladaCapturaDigitalMesario();
    return 71;
}

const void* volatile w161_sink;

struct SW161Roots {
    SW161Roots()
    {
        w161_sink = reinterpret_cast<const void*>(&CancelaUm);
    }
} w161_roots;

} // namespace
