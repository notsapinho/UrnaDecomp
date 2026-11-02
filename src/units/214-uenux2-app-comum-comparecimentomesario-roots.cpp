// Roots: reach unit 214's functions the way the target's callers do, until they land. Each has direct callers in the
// target and none of them is written, so each gets two call sites here and stays out of line; each stand-in has a body
// no target function has (two calls, then a constant or the two results' last bytes), and none is called:
// - comum::ListaArquivosNaoRegistrados (fn 5374): fns 1149 and 10451, one call each;
// - comum::CImprimirIdentificacaoMesariosFinal::GetNomeMesario (fn 5385): fn 12105, which calls it twice.
// Both return a class by value through a hidden result pointer, so they are declared through asm labels with that
// pointer first and called into buffers the stand-ins never destroy: nothing of libc++ is instantiated here. The
// member's `this` is a parameter of ours that its body never reads, as the target's wasm type has none.
extern "C" {
void w214_lista(void* resultado) __asm__("_ZN5comum27ListaArquivosNaoRegistradosEv");
void w214_nome(void* resultado, void* objeto, const void* titulo) __asm__(
    "_ZN5comum35CImprimirIdentificacaoMesariosFinal14GetNomeMesarioERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

// stands for fns 1149 and 10451
__attribute__((noinline)) int w214_arquivos(void* primeiro, void* segundo)
{
    w214_lista(primeiro);
    w214_lista(segundo);
    return 23;
}

// stands for fn 12105
__attribute__((noinline)) int w214_nomes(void* objeto, const void* primeiro, const void* segundo)
{
    alignas(4) unsigned char a[12];
    alignas(4) unsigned char b[12];
    w214_nome(a, objeto, primeiro);
    w214_nome(b, objeto, segundo);
    return a[11] + b[11];
}

int (*volatile w214_sink_arquivos)(void*, void*);
int (*volatile w214_sink_nomes)(void*, const void*, const void*);

struct SW214Roots {
    SW214Roots()
    {
        w214_sink_arquivos = w214_arquivos;
        w214_sink_nomes = w214_nomes;
    }
} w214_roots;

} // namespace
