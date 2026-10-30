// Roots: keep api::CSystem::GetFileSize and api::truncate (target fns 2759 and 5457) in the skeleton link. The target
// calls both directly and never through the table (ledger/callgraph.tsv): GetFileSize from 3653 and 11623 once and from
// 12134 twice, truncate from 2761 twice; none of those callers is reconstructed yet. The noinline callers below give
// GetFileSize two callers (three call sites) and truncate one with two call sites, the target's own shape, so binaryen
// keeps both bodies out of line as the target does; their bodies differ, so wasm-opt merges none of them, and no
// argument is the same constant at every call site, so dead-argument elimination folds none in. They are address-taken
// from a static constructor. Declared through asm labels with the wasm-level signatures; compiled as uenux2 code.
extern "C" {
int w2759_root_0(int) __asm__("_ZN3api7CSystem11GetFileSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w5457_root_0(int, long long, int) __asm__("_ZN3api8truncateEixRKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) int MesmoTamanho(int arquivoA, int arquivoB)
{
    return w2759_root_0(arquivoA) == w2759_root_0(arquivoB);
}

__attribute__((noinline)) int CabeEm(int arquivo, unsigned limite)
{
    return static_cast<unsigned>(w2759_root_0(arquivo)) <= limite;
}

__attribute__((noinline)) void Redimensiona(int descritor, long long tamanho, int arquivo)
{
    w5457_root_0(descritor, 0, arquivo);
    w5457_root_0(descritor, tamanho, arquivo);
}

void* volatile w2759_sink;

struct SW2759Roots {
    SW2759Roots()
    {
        w2759_sink = reinterpret_cast<void*>(&MesmoTamanho);
        w2759_sink = reinterpret_cast<void*>(&CabeEm);
        w2759_sink = reinterpret_cast<void*>(&Redimensiona);
    }
} w2759_roots;

} // namespace
