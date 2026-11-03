// Roots of src/units/283-uenux2-app-vota-operador-justificativa.mk: the vtables of vota::CEleitorMenor16Anos and
// vota::CAnoInformadoInvalido. In the target each is stored only by its class's constructor, inlined into
// vota::CPedeAnoNascimento::ProcessInput (fn 10590, pending: the fragment's -pending.cpp says what it waits for), the
// two vptr stores 1589740 and 1589668 (grep over build/out/splat/pieces/asm). Taking the vtables' addresses keeps
// every slot, ProcessInput's (10598, 10601) among them. Both sinks go when 10590 is in the link.
// CPedeAnoNascimento's and CEleitorImpedidoJustificarVotoCPF's vtables need none: their constructors are in the link,
// inlined into GetInst (fn 5418) and into vota::IConfirmaJustificativa::ProcessInput (fn 10588). The set insert's
// stand-in calls it through an asm label with the object's signature (its iterators passed as their node pointers), so
// this TU instantiates nothing; it goes when 7787 is in the link. Compiled with APP_CXXFLAGS.
extern "C" {
extern const char celeitormenor16anos_vt[] __asm__("_ZTVN4vota19CEleitorMenor16AnosE");
extern const char canoinformadoinvalido_vt[] __asm__("_ZTVN4vota21CAnoInformadoInvalidoE");
void w6733_root(void*, const void*, const void*) __asm__("_ZNSt3__23setIN7ecourna3app5dados25ETipoIdentificadorEleitorENS_4lessIS4_EENS_9allocatorIS4_EEE6insertB8ne210108INS_21__tree_const_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEEEvT_SH_");
}

namespace {

const void* volatile w283_sink;

// Stands for fn 7787, the other target caller of std::set<ecourna::app::dados::ETipoIdentificadorEleitor>'s range
// insert (fn 6733), which copies comum::CConfiguracaoEleicao's set at +604 into a set of its frame, as
// vota::CEleitorEncontrado::StartState (fn 10635) does.
__attribute__((noinline)) void CopiaTiposEmOutro(char* destino, char* configuracao)
{
    w6733_root(destino + 20, *reinterpret_cast<void**>(configuracao + 604), configuracao + 608);
}

struct SW283Roots {
    SW283Roots()
    {
        w283_sink = celeitormenor16anos_vt;
        w283_sink = canoinformadoinvalido_vt;
        w283_sink = reinterpret_cast<const void*>(&CopiaTiposEmOutro);
    }
} w283_roots;

} // namespace
