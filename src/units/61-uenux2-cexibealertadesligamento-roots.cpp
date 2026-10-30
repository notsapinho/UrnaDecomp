// Roots: keep vota::CExibeAlertaDesligamento's destructors (target fns 2883 and 12019, slots 0 and 1 of its vtable
// @1543004) and comum::CAppState's constructor (target fn 224) in the skeleton link the way the target keeps them.
//
// The vtable is referenced in the target only by the constructor, inlined into GetInst (fn 5979, not reconstructed),
// which with the static std::unique_ptr's exit-time destructor (fn 12022) also calls fn 2883 directly. Rooting the
// vtable keeps both destructors in the table, and the deleting destructor calls the other one; those two direct callers
// are not stood in for: the destructor is in the table, so binaryen keeps it out of line with the one caller our link
// gives it.
//
// Fn 224 has 97 direct callers in the target, the derived states' constructors (ledger/callgraph.tsv), none of them
// reconstructed. Two noinline callers stand in for them: both use the `this` it returns, as every target caller does,
// so binaryen keeps its result (the target's wasm type is (i32 i32)->(i32)), and they pass different flags, one a
// constant and one their own argument, so binaryen's dead-argument elimination folds none into the body (the target's
// callers pass every value from 0 to 7). Their bodies differ from each other and from every target function: each
// adds to the result or to the address. They are address-taken from a static constructor.
//
// Declared through asm labels with the wasm-level signatures (a constructor returns `this` before binaryen runs), so
// this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cexibealertadesligamento_vt[] __asm__("_ZTVN4vota24CExibeAlertaDesligamentoE");
int w224_root_0(int, int) __asm__("_ZN5comum9CAppStateC2Ei");
}

namespace {

__attribute__((noinline)) int ConstroiEstadoTecla(int estado)
{
    return w224_root_0(estado, 1) + 4;
}

__attribute__((noinline)) int ConstroiEstadoMembro(int bloco, int eventos)
{
    return w224_root_0(bloco + 16, eventos);
}

const void* volatile cexibealertadesligamento_sink;

struct SCExibeAlertaDesligamentoRoots {
    SCExibeAlertaDesligamentoRoots()
    {
        cexibealertadesligamento_sink = cexibealertadesligamento_vt;
        cexibealertadesligamento_sink = reinterpret_cast<const void*>(&ConstroiEstadoTecla);
        cexibealertadesligamento_sink = reinterpret_cast<const void*>(&ConstroiEstadoMembro);
    }
} cexibealertadesligamento_roots;

} // namespace
