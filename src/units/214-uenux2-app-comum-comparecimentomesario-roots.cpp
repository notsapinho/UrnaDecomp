// Roots: reach unit 214's functions the way the target's callers do, until they land.
// comum::CImprimirIdentificacaoMesariosFinal::GetNomeMesario (fn 5385) has one direct caller in the target, fn 12105,
// which calls it twice and is not written, so the stand-in gives it those two call sites and it stays out of line; the
// stand-in's body (the calls, then the results' last bytes) is no target function's, and nothing calls it.
// The stand-ins for comum::ListaArquivosNaoRegistrados (fn 5374), CControladorReconhecimentoMesario::GetInst (fn 1149)
// and GravaWsq (fn 5371) went: their target callers (1149 and 10451; 3614, 5382, 10316, 10337 and 10451; 5382 and
// 10451) are in the link.
// GetNomeMesario returns a class by value through a hidden result pointer, so it is declared through an asm label with
// that pointer first and called into buffers the stand-in never destroys: nothing of libc++ is instantiated here. Its
// `this` is a parameter of ours that its body never reads, as the target's wasm type has none.
extern "C" {
void w214_nome(void* resultado, void* objeto, const void* titulo) __asm__(
    "_ZN5comum35CImprimirIdentificacaoMesariosFinal14GetNomeMesarioERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

// stands for fn 12105
__attribute__((noinline)) int w214_nomes(void* objeto, const void* primeiro, const void* segundo)
{
    alignas(4) unsigned char a[12];
    alignas(4) unsigned char b[12];
    w214_nome(a, objeto, primeiro);
    w214_nome(b, objeto, segundo);
    return a[11] + b[11];
}

int (*volatile w214_sink_nomes)(void*, const void*, const void*);

struct SW214Roots {
    SW214Roots()
    {
        w214_sink_nomes = w214_nomes;
    }
} w214_roots;

} // namespace
