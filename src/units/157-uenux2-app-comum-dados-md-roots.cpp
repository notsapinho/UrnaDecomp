// Roots: keep this unit's comum::md members in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet, and every function below has direct callers in the target and no table slot
// (ledger/callgraph.tsv), so each noinline stand-in gives it two call sites and binaryen keeps its body out of line:
//   CCabecalhoEntidade's constructor (fn 1945), called once each by fns 2725, 11587, 11588, 11620, 11626 and 11629
//   (11587, 11626, 2725 and 11629 are written, units 305, 160, 293 and 200).
// CCarga's constructor (fn 2802) needs none now: its callers, fns 10290, 11587, 11626 and 11629, are all written
// (fragment 172, units 305, 160 and 200), and its stand-in went with 11629. CCarga::ValidaCriacao (fn 5670) needs none:
// the constructor, its one target caller, calls it twice.
// CEleitor's constructors (fns 5666 and 5668) need none: fn 11411, their one target caller, calls each twice.
// CEleitor::ValidaCriacao (fn 5667) has its two callers in celeitor.cpp's object, the two constructors.
// The stand-ins
// differ in their operators, so binaryen merges none of them. The target's wasm types keep every parameter of these
// functions, so no argument is the same constant at both call sites of a stand-in, and dead-argument elimination folds
// nothing in. Declared through asm labels with the object's signatures (a constructor returns this); address-taken from
// a static constructor.
extern "C" {
int w1945(int, int, int, int) __asm__("_ZN5comum2md18CCabecalhoEntidadeC1ERKN3api9CDateTimeEjNS0_14ETipoCabecalhoE");
}

namespace {

const void* volatile w157_sink;

__attribute__((noinline)) int Cabecalhos(int a, int b, int data, int codigo)
{
    return w1945(a, data, codigo, 0) - w1945(b, data + 12, codigo + 1, 2);
}

struct SRoots157 {
    SRoots157()
    {
        w157_sink = reinterpret_cast<const void*>(&Cabecalhos);
    }
} w157_roots;

} // namespace
