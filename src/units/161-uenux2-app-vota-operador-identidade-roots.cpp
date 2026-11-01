// Roots of src/units/161-uenux2-app-vota-operador-identidade.mk: the vtables of eight of its classes, and the second
// call sites of the static members, CLogVota members and the libc++ function whose target callers are not
// reconstructed yet.
//
// - Each vtable is referenced in the target only by its class's constructor, inlined into the function that creates the
//   singleton (fns 1256, 10635, 10489, 10627, 2735, 10443, 652 and 5424, none reconstructed). Taking the vtables'
//   addresses keeps every slot. vota::IEleitorImpedidoVotar's comes with CEleitorNaoEncontrado's destructor, which
//   calls the base's.
// - The functions below have direct callers in the target, two call sites or more each (ledger/callgraph.tsv), so
//   binaryen keeps them out of line; the stand-ins give them those call sites, each standing for the callers it names:
//   CControlaReconhecimento::PrimeiraTentativa (fn 5403, called twice by 10465), AtingiuLimiteVerificacoes (5404:
//   10447, and 10448, which is in the link), AtingiuLimiteTentativas and AvancaTentativa (5405 and 5406: 10473 and
//   10485), CLogVota::LogaHabilitacaoCanceladaConfirmacaoDado (2097: 10443, 10447, 10489, 10500 and 10626) and
//   LogaHabilitacaoCanceladaCapturaDigitalMesario (4522: 10451 and 10452), and libc++'s std::stoul (4661: 10443 and
//   10489). A stand-in goes when the target callers it names are in splat/matched.txt or written in the link.
// The stand-ins differ in their bytes, from each other and from every target function. Compiled with APP_CXXFLAGS.
#include <string>

#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

extern "C" {
extern const char ccontrolareconhecimento_vt[] __asm__("_ZTVN4vota23CControlaReconhecimentoE");
extern const char celeitorjavotou_vt[] __asm__("_ZTVN4vota15CEleitorJaVotouE");
extern const char cinformaanonascimentoerrado_vt[] __asm__("_ZTVN4vota27CInformaAnoNascimentoErradoE");
extern const char cidentidadeinvalida_vt[] __asm__("_ZTVN4vota19CIdentidadeInvalidaE");
extern const char cverificadadoeleitor_vt[] __asm__("_ZTVN4vota20CVerificaDadoEleitorE");
extern const char cdadoeleitornaoconfere_vt[] __asm__("_ZTVN4vota22CDadoEleitorNaoConfereE");
extern const char cpedeidentidade_vt[] __asm__("_ZTVN4vota15CPedeIdentidadeE");
extern const char celeitornaoencontrado_vt[] __asm__("_ZTVN4vota21CEleitorNaoEncontradoE");
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

// Stands for 10447 and 10452.
__attribute__((noinline)) int CancelaDois()
{
    CLogVota::GetInst().LogaHabilitacaoCanceladaCapturaDigitalMesario();
    CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
    return 73;
}

// Stands for 10443 and 10489, the two callers of libc++'s std::stoul (fn 4661).
__attribute__((noinline)) unsigned long LeDois(const std::string& primeiro, const std::string& segundo)
{
    return std::stoul(primeiro) + 3 * std::stoul(segundo);
}

const void* volatile w161_sink;

struct SW161Roots {
    SW161Roots()
    {
        w161_sink = ccontrolareconhecimento_vt;
        w161_sink = celeitorjavotou_vt;
        w161_sink = cinformaanonascimentoerrado_vt;
        w161_sink = cidentidadeinvalida_vt;
        w161_sink = cverificadadoeleitor_vt;
        w161_sink = cdadoeleitornaoconfere_vt;
        w161_sink = cpedeidentidade_vt;
        w161_sink = celeitornaoencontrado_vt;
        w161_sink = reinterpret_cast<const void*>(&PrimeiraDuasVezes);
        w161_sink = reinterpret_cast<const void*>(&LimiteVerificacoes);
        w161_sink = reinterpret_cast<const void*>(&TentaUm);
        w161_sink = reinterpret_cast<const void*>(&TentaDois);
        w161_sink = reinterpret_cast<const void*>(&CancelaUm);
        w161_sink = reinterpret_cast<const void*>(&CancelaDois);
        w161_sink = reinterpret_cast<const void*>(&LeDois);
    }
} w161_roots;

} // namespace
