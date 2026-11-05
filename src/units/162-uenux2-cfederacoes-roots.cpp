// Roots: keep comum::CFederacoes's GetInst in the skeleton link the way the target keeps it. It has direct callers and
// no table slot (ledger/callgraph.tsv), and one of them is not reconstructed yet, so a noinline stand-in gives it a call
// site of its own and binaryen keeps its body out of line. GetFederacao (fn 5799) needs none since its two target
// callers, 5922 and 11976, are in the link, and the destructor (fn 5800) none: its two target callers, GetInst and the
// pointer's exit destructor (11553), are both in the link.
// Declared through asm labels with the object's signatures; address-taken from a static constructor.
extern "C" {
int w2832() __asm__("_ZN5comum11CFederacoes7GetInstEv");
}

namespace {

const void* volatile cfederacoes_sink;

// Stands for fn 2832's caller 7787 (5922 and 11976 are in the link).
__attribute__((noinline)) int Federacoes() { return w2832() * 5 - 3; }

struct SCFederacoesRoots {
    SCFederacoesRoots()
    {
        cfederacoes_sink = reinterpret_cast<const void*>(&Federacoes);
    }
} cfederacoes_roots;

} // namespace
