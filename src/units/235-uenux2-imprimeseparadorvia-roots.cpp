// Roots: reach comum::CRelUtil::ImprimeSeparadorVia (target fn 5581, in crelutil.cpp, unit 123's source) the way the
// target does until its caller lands. Its one caller, fn 12110 (vota::CGeraBU's slot 2), calls it twice
// (ledger/callgraph.tsv) and is not reconstructed; w235_vias stands for it with two call sites, so binaryen keeps the
// function out of line, and passes values that differ between the two calls in every argument, as 12110's do, so that
// dead-argument elimination folds none. Its body is no target function's. Compiled as app code; the function is
// declared through its mangled name.
extern "C" {
void w235_separador(int, unsigned int, unsigned int) __asm__("_ZN5comum8CRelUtil19ImprimeSeparadorViaERN3api17CPaperFormBuilderEjj");
}

namespace {

__attribute__((noinline)) void w235_vias(int builder, unsigned int total)
{
    w235_separador(builder, 1, total);
    w235_separador(builder + 8, 3, total + 5);
}

void (*volatile w235_sink)(int, unsigned int);

struct SW235Roots {
    SW235Roots()
    {
        w235_sink = w235_vias;
    }
} w235_roots;

} // namespace
