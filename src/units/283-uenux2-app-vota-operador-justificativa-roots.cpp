// Roots of src/units/283-uenux2-app-vota-operador-justificativa.mk: a stand-in for fn 7787 (not written), the second
// target caller of std::set<comum::md::ETipoAbrangencia>'s range insert. It calls it through an asm label with the
// object's signature (its iterators passed as their node pointers), so this TU instantiates nothing; it goes when 7787
// is in the link. The vtables of the unit's classes need no sink: each is stored by its class's
// constructor, which the link holds (CEleitorMenor16Anos's and CAnoInformadoInvalido's inlined into
// vota::CPedeAnoNascimento::ProcessInput, fn 10590; CPedeAnoNascimento's into GetInst, fn 5418;
// CEleitorImpedidoJustificarVotoCPF's into vota::IConfirmaJustificativa::ProcessInput, fn 10588). Compiled with
// APP_CXXFLAGS.
extern "C" {
void w6733_root(void*, const void*, const void*) __asm__("_ZNSt3__23setIN5comum2md16ETipoAbrangenciaENS_4lessIS3_EENS_9allocatorIS3_EEE6insertB8ne210108INS_21__tree_const_iteratorIS3_PNS_11__tree_nodeIS3_PvEElEEEEvT_SG_");
}

namespace {

const void* volatile w283_sink;

// Stands for fn 7787, the other target caller of std::set<comum::md::ETipoAbrangencia>'s range insert (fn 6733), which
// copies comum::CConfiguracaoEleicao's set at +604 into a set of its frame, as vota::CEleitorEncontrado::StartState (fn
// 10635) does.
__attribute__((noinline)) void CopiaTiposEmOutro(char* destino, char* configuracao)
{
    w6733_root(destino + 20, *reinterpret_cast<void**>(configuracao + 604), configuracao + 608);
}

struct SW283Roots {
    SW283Roots()
    {
        w283_sink = reinterpret_cast<const void*>(&CopiaTiposEmOutro);
    }
} w283_roots;

} // namespace
