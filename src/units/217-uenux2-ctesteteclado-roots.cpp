// Roots of unit 217: the call sites the target gives two functions vota::testeteclado::CTesteTeclado::StartState (fn
// 11805) calls, whose other target callers are not in the link. binaryen inlines a function with one call site
// (docs/reference/facts/tool-traps.md X1), and each of these keeps its calls in the target (ledger/callgraph.tsv), so a
// stand-in gives each its second call site. Each stand-in names the target callers it stands for, and goes when they are
// in splat/matched.txt or written in the link. Compiled as app code; api::CTextBox::SetStatus is declared through an
// asm label, so this TU needs no uenux2 header.
#include <string>
#include <vector>

extern "C" {
void w217_status(void* caixa, int status) __asm__("_ZN3api8CTextBox9SetStatusENS_11ETextStatusE");
}

namespace {

// Stands for vota::testeteclado::CTesteTeclado::ProcessInput (fn 11804, pending in this unit), a caller of
// api::CTextBox::SetStatus (fn 940; its other caller, fn 5982, unit 37's, is in the link).
__attribute__((noinline)) void MudaStatus(void* caixa, int status)
{
    w217_status(caixa, status + 2);
}

// Stands for fn 11804, the other caller of std::vector<std::string>::at (fn 3854). An optnone function, where clang
// leaves the call; our link keeps the copy ctesteteclado.cpp.o emits, which links ahead of this object.
__attribute__((optnone, noinline)) unsigned long TamanhoTecla(std::vector<std::string>* teclas, unsigned long indice)
{
    return teclas->at(indice).size() + 3;
}

void (*volatile w217_sink_status)(void*, int);
unsigned long (*volatile w217_sink_tecla)(std::vector<std::string>*, unsigned long);

struct SW217Roots {
    SW217Roots()
    {
        w217_sink_status = MudaStatus;
        w217_sink_tecla = TamanhoTecla;
    }
} w217_roots;

} // namespace
