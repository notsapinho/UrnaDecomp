// Roots: keep comum::CGeradorResultados's constructor (target fn 5824) in the skeleton link the way the target reaches
// it: its one caller, vota::CGravaResultado::StartState (fn 12098, ledger/callgraph.tsv), calls it twice and is not
// reconstructed. This noinline caller stands for it with two call sites, every argument passed through, so binaryen
// keeps the constructor out of line and folds no argument in; it is address-taken from a static constructor. Declared
// through an asm label with the wasm-level signature (a constructor returns `this`; the std::shared_ptr argument is a
// pointer to the caller's copy, which the constructor releases); compiled with APP_CXXFLAGS.
extern "C" {
int w5824_root_0(int, int, int, int, int, int) __asm__("_ZN5comum18CGeradorResultadosC1ERKNSt3__26vectorINS1_10shared_ptrINS_9IGravadorEEENS1_9allocatorIS5_EEEERKNS2_INS3_INS_10IResultadoEEENS6_ISC_EEEERKNS_10CAssinadorEbS5_");
}

namespace {

__attribute__((noinline)) void GeraResultados(int gerador, int gravadores, int copiados, int assinador, int copiaMV,
    int gravador)
{
    w5824_root_0(gerador, gravadores, copiados, assinador, copiaMV, gravador);
    w5824_root_0(gerador + 84, gravadores, copiados, assinador, copiaMV, gravador + 8);
}

void* volatile w5824_sink;

struct SW5824Roots {
    SW5824Roots()
    {
        w5824_sink = reinterpret_cast<void*>(&GeraResultados);
    }
} w5824_roots;

} // namespace
