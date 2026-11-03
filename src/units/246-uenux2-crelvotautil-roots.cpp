// Roots of unit 246, for unit 31's api::CPaperFormBuilder::Show (fn 3671, in api/gui/cpaperformbuilder.cpp; its
// paragraph in src/units/31-uenux2-cformbuilder.mk says why its stand-ins are here). Show has three direct callers in
// the target (ledger/callgraph.tsv): fns 5591, 5592 (comum::CGeradorRelVersaoPacoteDados's slot 2, unit 287's, in the
// link) and 11902, the first and the last not written. Every one passes true for the bool, which binaryen's dead-argument elimination folds into the body (fn 3671 is
// (i32 i32 i32)->()), so the stand-in passes 1 at both of its calls; the two calls give Show two call sites, so binaryen
// keeps it out of line. It goes when those three callers are in the link. Declared through an asm label with the
// object's type, so this TU needs no uenux2 header; compiled as app code.
extern "C" void w246_show(int, int, int, int) __asm__(
    "_ZN3api17CPaperFormBuilder4ShowERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_b");

namespace {

volatile int w246_n;

// Stands for fns 5591 and 11902. It adds offsets to its argument and returns another sum, so its body is no
// target function's.
__attribute__((noinline)) int MostraRelatorio(int p)
{
    w246_show(p, p + 12, p + 24, 1);
    w246_show(p + 4, p + 36, p + 48, 1);
    return p + 7;
}

struct SW246Roots {
    SW246Roots() { w246_n = MostraRelatorio(w246_n); }
} w246_roots;

} // namespace
