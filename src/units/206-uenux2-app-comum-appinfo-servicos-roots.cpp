// Roots: keep what unit 206 reaches in the skeleton link the way the target reaches it.
//
// comum::CServicoEstadoGeral's constructor (target fn 1941) has five direct callers in the target, fns 2273, 3333,
// 3897, 10243 and 11572. 3897, binaryen's merge of the three derived classes' constructors, is in the link; the other
// four are not. UmGeral and DoisGerais stand for those four, with three call sites, each reading the returned object as
// every target caller does (2273 and 11572 pass it to fn 3791, 3333 and 10243 to the save, fns 3592 and its slot 422),
// and passing the origin as a variable and as both constants, so dead-argument elimination folds nothing in. Their
// bodies add offsets, so neither is a target function's. They go when those four callers are in the link.
//
// CServicoEstadoGeralVota's, -Gap's and -SA's constructors (thunks 3787, 5812 and 11566 of fn 3897) fill table slots
// 438, 431 and 434, which fn 10212 (mock/app/comum/cappinfobuilder.cpp, written, not in the link) passes to invoke_*;
// 6039 and 7787 call 3787, and 7787 calls 5812, directly (7787 is not in the link; 6039 is). Taking each constructor's
// address stands for 10212's slots, and keeps it out of line whatever its direct callers: binaryen inlines no function
// the table holds (docs/reference/facts/tool-traps.md X1). Each line goes when 10212 is in the link. The constructors
// store their classes' vptrs, so the vtables need no sink.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The constructors return their object, as at the target's call sites, so their labels return one.
extern "C" {
char* r206_geral(void* objeto, int origem) __asm__("_ZN5comum19CServicoEstadoGeralC1ENS_12EFlashOrigemE");
char* r206_vota(void* objeto, int origem, int turno) __asm__(
    "_ZN5comum23CServicoEstadoGeralVotaC1ENS_12EFlashOrigemENS_10EUrnaTurnoE");
char* r206_gap(void* objeto, int origem, int turno) __asm__(
    "_ZN5comum22CServicoEstadoGeralGapC1ENS_12EFlashOrigemENS_10EUrnaTurnoE");
char* r206_sa(void* objeto, int origem, int turno) __asm__(
    "_ZN5comum21CServicoEstadoGeralSAC1ENS_12EFlashOrigemENS_10EUrnaTurnoE");
void r206_salva_geral(void* servico, const void* estado) __asm__(
    "_ZN5comum14IServicoEstadoINS_2md15estadoaplicacao12CEstadoGeralENS_3asn21CConversorEstadoGeralEE5SalvaERKS3_");
void r206_salva_vota(void* servico, const void* estado) __asm__(
    "_ZN5comum14IServicoEstadoINS_2md15estadoaplicacao16CEstadoGeralVotaENS_3asn25CConversorEstadoGeralVotaEE5SalvaERKS3_");
void r206_salva_gap(void* servico, const void* estado) __asm__(
    "_ZN5comum14IServicoEstadoINS_2md15estadoaplicacao15CEstadoGeralGapENS_3asn24CConversorEstadoGeralGapEE5SalvaERKS3_");
void r206_salva_sa(void* servico, const void* estado) __asm__(
    "_ZN5comum14IServicoEstadoINS_2md15estadoaplicacao14CEstadoGeralSAENS_3asn23CConversorEstadoGeralSAEE5SalvaERKS3_");
}

namespace {

const void* volatile r206_sink;

// stands for fns 2273, 3333, 10243 and 11572, with DoisGerais
__attribute__((noinline)) char* UmGeral(char* destino, int origem)
{
    return r206_geral(destino + 8, origem) + 4;
}

// stands for fns 2273, 3333, 10243 and 11572, with UmGeral
__attribute__((noinline)) char* DoisGerais(char* destino)
{
    char* externa = r206_geral(destino + 16, 1);
    char* interna = r206_geral(destino + 28, 0);
    return interna + (externa - destino);
}

struct SRoots206 {
    SRoots206()
    {
        r206_sink = reinterpret_cast<const void*>(&UmGeral);
        r206_sink = reinterpret_cast<const void*>(&DoisGerais);
        // stand for fn 10212's table slots 438, 431 and 434
        r206_sink = reinterpret_cast<const void*>(&r206_vota);
        r206_sink = reinterpret_cast<const void*>(&r206_gap);
        r206_sink = reinterpret_cast<const void*>(&r206_sa);
        // stand for fn 10243's table slot 422 and fn 10212's slots 440, 433 and 436
        r206_sink = reinterpret_cast<const void*>(&r206_salva_geral);
        r206_sink = reinterpret_cast<const void*>(&r206_salva_vota);
        r206_sink = reinterpret_cast<const void*>(&r206_salva_gap);
        r206_sink = reinterpret_cast<const void*>(&r206_salva_sa);
    }
} roots206;

} // namespace
