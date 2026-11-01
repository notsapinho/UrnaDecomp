// Roots: keep api::CSystem::GetFileSize (target fn 2759) in the skeleton link. The target calls it and api::truncate
// (5457) directly and never through the table (ledger/callgraph.tsv): GetFileSize from 3653 and 11623 once and from
// 12134 twice, truncate from 2761 twice. ZeroFill (2761) is reconstructed and calls truncate twice, the target's own
// shape. Of GetFileSize's callers, 11623 (CGravadorEnvelopeArquivo::LeConteudo, unit 160) is reconstructed; the
// noinline callers below stand for the others, MesmoTamanho for 12134 and CabeEm for 3653, so binaryen keeps it out of
// line as the target does.
// They also keep CSystem::ExistFile, ExistDir and ZeroFill (target fns 412, 5459 and 2761), none of whose callers is
// reconstructed: ExistFile is called directly by 23 target functions (1487, 2725, 3653 and others) and its address is
// in the table (slot 3567), so it is address-taken here and called from two stand-ins; ExistDir is called once each by
// 5572 and 5821, so it gets two call sites. ZeroFill is called by 2760 (RemoveFile, reconstructed) and 5458 once and
// 5455 twice: ZeraAmbos stands for 5458 and 5455, which still wait.
// RemoveFile (target fn 2760) is called directly by 1487 and 7160 once and 6737 twice, none reconstructed: RemoveDois
// gives it two call sites.
// The stand-ins' bodies differ, so wasm-opt merges none of them, and no argument is the same constant at every call
// site, so dead-argument elimination folds none in. They are address-taken from a static constructor. Declared through
// asm labels with the wasm-level signatures; compiled as uenux2 code.
extern "C" {
int w2759_root_0(int) __asm__("_ZN3api7CSystem11GetFileSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w412_root_0(int) __asm__("_ZN3api7CSystem9ExistFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w5459_root_0(int) __asm__("_ZN3api7CSystem8ExistDirERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2761_root_0(int) __asm__("_ZN3api7CSystem8ZeroFillERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2760_root_0(int) __asm__("_ZN3api7CSystem10RemoveFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
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

__attribute__((noinline)) int ArquivoNoDiretorio(int arquivo, int diretorio)
{
    return w412_root_0(arquivo) && w5459_root_0(diretorio);
}

__attribute__((noinline)) int ContaRecursos(int arquivo, int diretorio, int outro)
{
    return w412_root_0(arquivo) + w412_root_0(outro) * 2 + w5459_root_0(diretorio) * 4;
}

__attribute__((noinline)) void ZeraAmbos(int arquivoA, int arquivoB)
{
    w2761_root_0(arquivoA);
    w2761_root_0(arquivoB);
}

__attribute__((noinline)) void RemoveDois(int arquivoA, int arquivoB)
{
    w2760_root_0(arquivoA);
    w2760_root_0(arquivoB);
}

void* volatile w2759_sink;

struct SW2759Roots {
    SW2759Roots()
    {
        w2759_sink = reinterpret_cast<void*>(&MesmoTamanho);
        w2759_sink = reinterpret_cast<void*>(&CabeEm);
        w2759_sink = reinterpret_cast<void*>(&ArquivoNoDiretorio);
        w2759_sink = reinterpret_cast<void*>(&ContaRecursos);
        w2759_sink = reinterpret_cast<void*>(&ZeraAmbos);
        w2759_sink = reinterpret_cast<void*>(&RemoveDois);
        w2759_sink = reinterpret_cast<void*>(&w412_root_0);
    }
} w2759_roots;

} // namespace
