// Roots: keep comum::CEleitores::DynamicCreate (fn 5761, celeitores.cpp) in the skeleton link the way the target reaches
// it. Its one target caller is fn 6737 (under vota::CGeraDadosDinamicos::StartState, 11865, and votaInit), which calls
// it twice, each time with another database file's path (2826's "uenux.db" and 5762's), and is not written:
//   CriaDinamicos   stands for fn 6737's two calls, with two different paths so that no argument folds; it goes when
//                   6737 lands
// The function is declared through an asm label with the object's signature, so this TU instantiates nothing; the
// body differs from every target function's.
extern "C" {
void w5761(int, int) __asm__(
    "_ZNK5comum10CEleitores13DynamicCreateERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) void CriaDinamicos(int eleitores, int banco)
{
    w5761(eleitores, banco);
    w5761(eleitores, banco + 12);
}

const void* volatile dinamicos_sink;

struct SDinamicosRoots {
    SDinamicosRoots() { dinamicos_sink = reinterpret_cast<const void*>(&CriaDinamicos); }
} dinamicos_roots;

} // namespace
