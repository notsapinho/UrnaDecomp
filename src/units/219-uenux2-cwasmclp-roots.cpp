// Roots of unit 219. api::CLp's destructor (fn 5978, in mock/app/simulador/wasm/cwasmclp.cpp) has two direct callers in
// the target (ledger/callgraph.tsv): CLp's singleton accessor (fn 3876), which destroys the object a new one replaces,
// and the exit-time destructor of the static pointer it fills (fn 12016). Neither is written. The stand-in below calls
// the destructor twice for them and drops its result, as both do, so binaryen keeps the destructor out of line and
// removes the `this` it returns, as the target's (i32)->() shows. It goes when those callers are in splat/matched.txt or
// written in the link. Declared through an asm label, int for the destructor's `this`, so this TU needs no uenux2 header;
// compiled as app code.
extern "C" int w219_clp_d2(int) __asm__("_ZN3api3CLpD2Ev");

namespace {

volatile int w219_n;

// Stands for fns 3876 and 12016. It adds an offset to its argument and returns another sum, so its body is no target
// function's.
__attribute__((noinline)) int DestroiLp(int p)
{
    w219_clp_d2(p);
    w219_clp_d2(p + 12);
    return p + 5;
}

struct SW219Roots {
    SW219Roots() { w219_n = DestroiLp(w219_n); }
} w219_roots;

} // namespace
