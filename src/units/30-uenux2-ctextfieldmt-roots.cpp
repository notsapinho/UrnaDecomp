// Roots: keep the api::CTextFieldMT constructor (target fn 1262) in the skeleton link. The target calls it directly from
// eight functions (180 619 651 1152 2753 5409 5419 10388, ledger/callgraph.tsv; each a
// std::shared_ptr<IFormField<IScreenMT>>(new CTextFieldMT(...)) on a 48-byte block), none reconstructed yet and none
// through the table. Two noinline callers with different bodies give it more than one call site, so binaryen keeps it
// out of line, and both use the `this` it returns, so binaryen's dead-argument elimination keeps the target's
// (i32 i32 i32)->(i32). They are address-taken from a static constructor. Its vtable, and through it the destructors and
// IFormField<IScreenMT>::GetTypeName, are kept by the constructor's vptr store. Declared through an asm label with the
// wasm-level signature (a constructor returns this); compiled as uenux2 code.
#include <new>

extern "C" {
int w1262_root_0(int, int, int) __asm__("_ZN3api12CTextFieldMTC1ERKNS_6SPointERKNSt3__210shared_ptrINS_5ITextEEE");
}

namespace {

__attribute__((noinline)) int CriaCampoTextoMT(int posicao, int texto)
{
    return w1262_root_0(static_cast<int>(reinterpret_cast<__INTPTR_TYPE__>(::operator new(48))), posicao, texto);
}

__attribute__((noinline)) int CriaCamposTextoMT(int campos, int posicao, int texto)
{
    const int primeiro = w1262_root_0(campos, posicao, texto);
    const int segundo = w1262_root_0(campos + 48, posicao + 4, texto);
    return primeiro == segundo ? 0 : segundo;
}

void* volatile w1262_sink;

struct SW1262Roots {
    SW1262Roots()
    {
        w1262_sink = reinterpret_cast<void*>(&CriaCampoTextoMT);
        w1262_sink = reinterpret_cast<void*>(&CriaCamposTextoMT);
    }
} w1262_roots;

} // namespace
