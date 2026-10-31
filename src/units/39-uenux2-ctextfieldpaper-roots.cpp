// Roots: keep the api::CTextFieldPaper constructor (target fn 2771) in the skeleton link. The target calls it directly
// from four functions (193 604 5613 12105, ledger/callgraph.tsv; each a
// std::shared_ptr<IFormField<IPaper>>(new CTextFieldPaper(...)) on a 36-byte block), none through the table. 193 and
// 604 are written, in cpaperformbuilder.cpp; 5613 and 12105 are not, and the two noinline callers here stand for them.
// Their bodies differ and both use the `this` it returns, so binaryen's dead-argument elimination keeps the target's
// (i32 i32 i32)->(i32). They are address-taken from a static constructor. Its vtable, and through it Draw, the
// destructors and IFormField<IPaper>::GetTypeName, are kept by the constructor's vptr store. Declared through an asm
// label with the wasm-level signature (a constructor returns this); compiled as app code.
#include <new>

extern "C" {
int w2771_root_0(int, int, int) __asm__("_ZN3api15CTextFieldPaperC1ERKNSt3__210shared_ptrINS_5ITextEEENS_6IPaper6EStyleE");
}

namespace {

__attribute__((noinline)) int CriaCampoTextoPaper(int texto, int estilo)
{
    return w2771_root_0(static_cast<int>(reinterpret_cast<__INTPTR_TYPE__>(::operator new(36))), texto, estilo);
}

__attribute__((noinline)) int CriaCamposTextoPaper(int campos, int texto, int estilo)
{
    const int primeiro = w2771_root_0(campos, texto, estilo);
    const int segundo = w2771_root_0(campos + 36, texto + 8, estilo + 1);
    return primeiro == segundo ? 0 : segundo;
}

void* volatile w2771_sink;

struct SW2771Roots {
    SW2771Roots()
    {
        w2771_sink = reinterpret_cast<void*>(&CriaCampoTextoPaper);
        w2771_sink = reinterpret_cast<void*>(&CriaCamposTextoPaper);
    }
} w2771_roots;

} // namespace
