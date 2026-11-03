// Roots of src/units/161-uenux2-app-vota-operador-identidade.mk: the vtables of four of its classes, and the second
// call sites of the static members, CLogVota members and the libc++ function whose target callers are not
// reconstructed yet.
//
// - Each vtable is referenced in the target only by its class's constructor, inlined into the function that creates the
//   singleton (fns 1256, 10489, 10627 and 10443, none reconstructed). Taking the vtables' addresses keeps every slot.
//   vota::CVerificaDadoEleitor's constructor is in the link, inlined into its GetInst (fn 2735), so no sink keeps that
//   vtable. vota::CEleitorNaoEncontrado's constructor is in the link, inlined into its GetInst (fn 5424), which
//   vota::CProcuraEleitor::StartState (10631) and CEleitorEncontrado::StartState (10635, both unit 104's) call, and
//   CEleitorJaVotou's, inlined into its GetInst, which 10635 holds (its file is unit 104's now), so no sink keeps those
//   two vtables; vota::IEleitorImpedidoVotar's comes with its constructor (fn 1905), which 5424 calls. CPedeIdentidade's
//   constructor is in the link, inlined into its GetInst (fn 652).
// - The functions below have direct callers in the target, two call sites or more each (ledger/callgraph.tsv), so
//   binaryen keeps them out of line; the stand-ins give them those call sites, each standing for the callers it names:
//   CControlaReconhecimento::PrimeiraTentativa (fn 5403, called twice by 10465), AtingiuLimiteVerificacoes (5404:
//   10447, and 10448, which is in the link), AtingiuLimiteTentativas and AvancaTentativa (5405 and 5406: 10473 and
//   10485), CLogVota::LogaHabilitacaoCanceladaConfirmacaoDado (2097: 10443, 10447, 10489 and 10500; 10626 is in the
//   link) and LogaHabilitacaoCanceladaCapturaDigitalMesario (4522: 10451; 10452 is in the link), libc++'s std::stoul
//   (4661: 10443 and 10489), and CPedeIdentidade::GetInst (652: 22 target callers, of which
//   CEleitorVotouNaoVotou::ProcessInput, 10430, and the ones the stand-in's comment names are in the link). A stand-in goes when the target callers it names are in splat/matched.txt or written in
//   the link.
// The stand-ins differ in their bytes, from each other and from every target function. Compiled with APP_CXXFLAGS.
#include <string>

#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

extern "C" {
extern const char ccontrolareconhecimento_vt[] __asm__("_ZTVN4vota23CControlaReconhecimentoE");
extern const char cinformaanonascimentoerrado_vt[] __asm__("_ZTVN4vota27CInformaAnoNascimentoErradoE");
extern const char cidentidadeinvalida_vt[] __asm__("_ZTVN4vota19CIdentidadeInvalidaE");
extern const char cdadoeleitornaoconfere_vt[] __asm__("_ZTVN4vota22CDadoEleitorNaoConfereE");
int w161_pede_identidade() __asm__("_ZN4vota15CPedeIdentidade7GetInstEv");
}

namespace {

using vota::CControlaReconhecimento;
using vota::CLogVota;

// Stands for 10465, which calls PrimeiraTentativa twice.
__attribute__((noinline)) int PrimeiraDuasVezes()
{
    return CControlaReconhecimento::PrimeiraTentativa() + 2 * CControlaReconhecimento::PrimeiraTentativa();
}

// Stands for 10447.
__attribute__((noinline)) int LimiteVerificacoes()
{
    return CControlaReconhecimento::AtingiuLimiteVerificacoes() ? 43 : 47;
}

// Stands for 10473.
__attribute__((noinline)) int TentaUm()
{
    if (CControlaReconhecimento::AtingiuLimiteTentativas()) {
        return 53;
    }
    CControlaReconhecimento::AvancaTentativa();
    return 59;
}

// Stands for 10485.
__attribute__((noinline)) int TentaDois()
{
    CControlaReconhecimento::AvancaTentativa();
    return CControlaReconhecimento::AtingiuLimiteTentativas() ? 61 : 67;
}

// Stands for 10443 and 10451.
__attribute__((noinline)) int CancelaUm()
{
    CLogVota& log = CLogVota::GetInst();
    log.LogaHabilitacaoCanceladaConfirmacaoDado();
    log.LogaHabilitacaoCanceladaCapturaDigitalMesario();
    return 71;
}

// Stands for 10447 (its call of 4522 stood for 10452, which is in the link: unit 221).
__attribute__((noinline)) int CancelaDois()
{
    CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
    return 73;
}

// Stands for 10443 and 10489, the two callers of libc++'s std::stoul (fn 4661).
__attribute__((noinline)) unsigned long LeDois(const std::string& primeiro, const std::string& segundo)
{
    return std::stoul(primeiro) + 3 * std::stoul(segundo);
}

// Stands for the target's other callers of CPedeIdentidade::GetInst (fn 652): 10209, 10404, 10443, 10447, 10590 and
// 10689 (in the link: 2295, the body binaryen merges from the five states' slot 7, 10452 and 10626, units 161, 221,
// 278, 283 and 277; 10217, 10435, 10527, 10646 and 10762, units 165, 152, 281, 104 and 119; 10588 and 10624, units
// 174's and 161's; and 10718, 10721, 10731, 10734 and 10751, unit 277's).
__attribute__((noinline)) int PedeIdentidade()
{
    return w161_pede_identidade() + 89;
}

const void* volatile w161_sink;

struct SW161Roots {
    SW161Roots()
    {
        w161_sink = ccontrolareconhecimento_vt;
        w161_sink = cinformaanonascimentoerrado_vt;
        w161_sink = cidentidadeinvalida_vt;
        w161_sink = cdadoeleitornaoconfere_vt;
        w161_sink = reinterpret_cast<const void*>(&PrimeiraDuasVezes);
        w161_sink = reinterpret_cast<const void*>(&LimiteVerificacoes);
        w161_sink = reinterpret_cast<const void*>(&TentaUm);
        w161_sink = reinterpret_cast<const void*>(&TentaDois);
        w161_sink = reinterpret_cast<const void*>(&CancelaUm);
        w161_sink = reinterpret_cast<const void*>(&CancelaDois);
        w161_sink = reinterpret_cast<const void*>(&LeDois);
        w161_sink = reinterpret_cast<const void*>(&PedeIdentidade);
    }
} w161_roots;

} // namespace
