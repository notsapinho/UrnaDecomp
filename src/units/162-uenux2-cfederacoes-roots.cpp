// Roots: keep comum::CFederacoes's GetInst and GetFederacao in the skeleton link the way the target keeps them. Their
// users are not reconstructed yet. Both have direct callers and no table slot (ledger/callgraph.tsv), so a noinline
// stand-in gives each two call sites and binaryen keeps its body out of line. The destructor (fn 5800) needs none: its
// two target callers, GetInst and the pointer's exit destructor (11553), are both in the link. The stand-ins differ in
// their operators, and take their arguments as parameters, so binaryen merges none of them and folds no argument in.
// Declared through asm labels with the object's signatures; address-taken from a static constructor.
extern "C" {
int w2832() __asm__("_ZN5comum11CFederacoes7GetInstEv");
int w5799(int, int) __asm__("_ZNK5comum11CFederacoes12GetFederacaoEt");
}

namespace {

const void* volatile cfederacoes_sink;

// Stands for fn 2832's callers: 5922, 7787, 11976.
__attribute__((noinline)) int Federacoes() { return w2832() - 5 * w2832(); }
// Stands for fn 5799's callers: 5922, 11976.
__attribute__((noinline)) int FederacoesDoPartido(int a, int b) { return w5799(a, b) ^ w5799(a, b + 1); }

struct SCFederacoesRoots {
    SCFederacoesRoots()
    {
        cfederacoes_sink = reinterpret_cast<const void*>(&Federacoes);
        cfederacoes_sink = reinterpret_cast<const void*>(&FederacoesDoPartido);
    }
} cfederacoes_roots;

} // namespace
