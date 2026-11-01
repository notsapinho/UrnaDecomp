// Roots: keep api::CSystem::GetFileSize (target fn 2759) in the skeleton link. The target calls it and api::truncate
// (5457) directly and never through the table (ledger/callgraph.tsv): GetFileSize from 3653 and 11623 once and from
// 12134 twice, truncate from 2761 twice. ZeroFill (2761) is reconstructed and calls truncate twice, the target's own
// shape. Of GetFileSize's callers, 11623 (CGravadorEnvelopeArquivo::LeConteudo, unit 160) and 3653
// (api::CEncryptedFile::Load, unit 128) are reconstructed; the noinline caller below, MesmoTamanho, stands for the
// other, 12134, so binaryen keeps it out of line as the target does.
// They also keep CSystem::ExistFile, ExistDir and ZeroFill (target fns 412, 5459 and 2761), whose callers are not
// reconstructed but for 3653 and 2760: ExistFile is called directly by 23 target functions (1487, 2725, 3653 and
// others) and its address is in the table (slot 3567), so it is address-taken here and called from two stand-ins;
// ExistDir is called once each by 5572 and 5821, so it gets two call sites. ZeroFill is called by 2760 (RemoveFile)
// and 5458 (RemoveTree) once, both reconstructed, and by 5455 twice: ZeraAmbos stands for 5455, which still waits.
// RemoveFile (target fn 2760) is called directly by 1487 and 7160 once and 6737 twice, none reconstructed: RemoveDois
// gives it two call sites.
// CopyFile (target fn 378) is called directly by 15 target functions (1836, 2725, 3333, 4657, 4682, 4687, 5371, 5873,
// 5874, 6737, 7174, 11630, 11631, 11632 and 12098), none reconstructed: CopiaDuas gives it two call sites. Every target
// caller passes the same value for one of its two bools, which the target's type (i32 i32 i32) has folded, and 0 or 1
// for the other (2725 passes 1, the rest 0): CopiaDuas passes the folded one as 1 at both sites, the other as 0 and 1.
// Rename has no target index of its own: binaryen inlines it into its one caller, fn 11584 (comum::CGravadorLog's slot
// 7, not reconstructed). RenomeiaUma stands for 11584 and calls it once, so binaryen inlines it there too; its code
// then gives the std::format arguments' builder that CopyFile shares (fn 5456) the second caller it has in the target.
// libc's utime (fn 6238) is called by CopyFile and by 7-Zip's fn 2585, which our link does not hold: AjustaHora stands
// for 2585, so binaryen keeps utime out of line as the target does.
// api::RemoveTree (target fn 5458) is called by itself and by 5455 (csystem.cpp's TemporaryPath, PrepareReplace and
// ReplaceResource records), not reconstructed: RemoveUmaArvore stands for 5455 with one call site, which with
// RemoveTree's own recursive call gives it the two the target has.
// api::GetFreeSpace, GetUsedSpace and GetMemInfo (target fns 5454, 5453 and 5463) are each called twice by 10226
// (vota::CThreadMonitor's slot 2), not reconstructed: MedeEspaco stands for it with two call sites of each.
// The stand-ins' bodies differ, so wasm-opt merges none of them, and no argument is the same constant at every call
// site but CopyFile's folded bool, which the target folds too, so dead-argument elimination folds no other. They are
// address-taken from a static constructor. Declared through asm labels with the wasm-level signatures; compiled as
// uenux2 code.
#include <utime.h>

extern "C" {
int w2759_root_0(int) __asm__("_ZN3api7CSystem11GetFileSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w412_root_0(int) __asm__("_ZN3api7CSystem9ExistFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w5459_root_0(int) __asm__("_ZN3api7CSystem8ExistDirERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2761_root_0(int) __asm__("_ZN3api7CSystem8ZeroFillERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2760_root_0(int) __asm__("_ZN3api7CSystem10RemoveFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w378_root_0(int, int, int, int) __asm__("_ZN3api7CSystem8CopyFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_bb");
int w5458_root_0(int) __asm__("_ZN3api10RemoveTreeERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
long long w5454_root_0(int) __asm__("_ZN3api12GetFreeSpaceERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
long long w5453_root_0(int) __asm__("_ZN3api12GetUsedSpaceERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
int w5463_root_0(int) __asm__("_ZN3api10GetMemInfoERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
void w11584_root_0(int, int) __asm__("_ZN3api7CSystem6RenameERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_");
}

namespace {

__attribute__((noinline)) int MesmoTamanho(int arquivoA, int arquivoB)
{
    return w2759_root_0(arquivoA) == w2759_root_0(arquivoB);
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

__attribute__((noinline)) void CopiaDuas(int origem, int destinoA, int destinoB)
{
    w378_root_0(origem, destinoA, 0, 1);
    w378_root_0(destinoA, destinoB, 1, 1);
}

__attribute__((noinline)) void RenomeiaUma(int origem, int destino)
{
    w11584_root_0(destino, origem);
}

__attribute__((noinline)) int RemoveUmaArvore(int diretorio)
{
    return w5458_root_0(diretorio + 12) == 0;
}

__attribute__((noinline)) long long MedeEspaco(int caminhoA, int caminhoB)
{
    return w5454_root_0(caminhoA) * 3 + w5454_root_0(caminhoB) - w5453_root_0(caminhoA) - w5453_root_0(caminhoB) * 2 +
           w5463_root_0(caminhoA) - w5463_root_0(caminhoB + 4);
}

__attribute__((noinline)) int AjustaHora(const char* arquivo)
{
    return utime(arquivo, nullptr) + 1;
}

void* volatile w2759_sink;

struct SW2759Roots {
    SW2759Roots()
    {
        w2759_sink = reinterpret_cast<void*>(&MesmoTamanho);
        w2759_sink = reinterpret_cast<void*>(&ArquivoNoDiretorio);
        w2759_sink = reinterpret_cast<void*>(&ContaRecursos);
        w2759_sink = reinterpret_cast<void*>(&ZeraAmbos);
        w2759_sink = reinterpret_cast<void*>(&RemoveDois);
        w2759_sink = reinterpret_cast<void*>(&w412_root_0);
        w2759_sink = reinterpret_cast<void*>(&CopiaDuas);
        w2759_sink = reinterpret_cast<void*>(&RenomeiaUma);
        w2759_sink = reinterpret_cast<void*>(&AjustaHora);
        w2759_sink = reinterpret_cast<void*>(&RemoveUmaArvore);
        w2759_sink = reinterpret_cast<void*>(&MedeEspaco);
    }
} w2759_roots;

} // namespace
