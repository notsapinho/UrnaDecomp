// Roots: keep what unit 206 reaches in the skeleton link the way the target reaches it.
//
// comum::CServicoEstadoGeral's constructor (target fn 1941) has five direct callers in the target, fns 2273, 3333,
// 3897, 10243 and 11572, none of them in the link; with no caller wasm-ld drops it, and with one binaryen inlines it.
// UmGeral and DoisGerais stand for them, with three call sites, each reading the returned object as every target caller
// does (3897, 2273 and 11572 pass it to fn 3791, 3333 and 10243 to the save, fns 3592 and its slot 422), and passing
// the origin as a variable and as both constants, so dead-argument elimination folds nothing in. Their bodies add
// offsets, so neither is a target function's. They go when the five callers are in the link.
//
// CServicoEstadoGeralVota's, -Gap's and -SA's vtables are referenced in the target only by their constructors (the
// thunks 3787, 5812 and 11566 pass them to fn 3897), which are not written: taking each vtable's address keeps its
// slots, GetPathArquivo (fns 11568, 11567, 11565) among them. Each sink line goes when its class's constructor is in
// the link. CServicoEstadoGeral's vtable needs none: its constructor stores it.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The constructor returns its object, as at the target's call sites, so its label returns one.
extern "C" {
extern const char r206_vt_vota[] __asm__("_ZTVN5comum23CServicoEstadoGeralVotaE");
extern const char r206_vt_gap[] __asm__("_ZTVN5comum22CServicoEstadoGeralGapE");
extern const char r206_vt_sa[] __asm__("_ZTVN5comum21CServicoEstadoGeralSAE");
char* r206_geral(void* objeto, int origem) __asm__("_ZN5comum19CServicoEstadoGeralC1ENS_12EFlashOrigemE");
}

namespace {

const void* volatile r206_sink;

// stands for fns 2273, 3333, 3897, 10243 and 11572, with DoisGerais
__attribute__((noinline)) char* UmGeral(char* destino, int origem)
{
    return r206_geral(destino + 8, origem) + 4;
}

// stands for fns 2273, 3333, 3897, 10243 and 11572, with UmGeral
__attribute__((noinline)) char* DoisGerais(char* destino)
{
    char* externa = r206_geral(destino + 16, 1);
    char* interna = r206_geral(destino + 28, 0);
    return interna + (externa - destino);
}

struct SRoots206 {
    SRoots206()
    {
        r206_sink = r206_vt_vota;
        r206_sink = r206_vt_gap;
        r206_sink = r206_vt_sa;
        r206_sink = reinterpret_cast<const void*>(&UmGeral);
        r206_sink = reinterpret_cast<const void*>(&DoisGerais);
    }
} roots206;

} // namespace
