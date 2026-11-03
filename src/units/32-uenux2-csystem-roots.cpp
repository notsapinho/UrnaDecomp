// Roots: keep api::CSystem::GetFileSize (target fn 2759) in the skeleton link. The target calls it and api::truncate
// (5457) directly and never through the table (ledger/callgraph.tsv): GetFileSize from 3653 and 11623 once and from
// 12134 twice, truncate from 2761 twice. ZeroFill (2761) is reconstructed and calls truncate twice, the target's own
// shape. Of GetFileSize's callers, 11623 (CGravadorEnvelopeArquivo::LeConteudo, unit 160) and 3653
// (api::CEncryptedFile::Load, unit 128) are reconstructed; the noinline caller below, MesmoTamanho, stands for the
// other, 12134, so binaryen keeps it out of line as the target does.
// They also keep CSystem::ExistFile and ZeroFill (target fns 412 and 2761), whose callers are not
// reconstructed but for 3653, 2760 and 1487: ExistFile is called directly by 23 target functions (1487, 2725, 3653 and
// others) and its address is in the table (slot 3567), so it is address-taken here and called twice from a stand-in;
// ExistDir is called once each by 5572 and 5821, both in the link (unit 122's CompactaWsq, unit 179's ValidaConteudo).
// IsEmptyDir (target fn 2762) is called once each by 5572, 5821, 11167 and 12134: DiretorioVazio stands for the two not
// written, 11167 and 12134. ZeroFill is called by 2760
// (RemoveFile) and 5458 (RemoveTree) once and by 5455 (CSystem::ReplaceFile) twice, all reconstructed.
// RemoveFile (target fn 2760) is called directly by 1487 and 7160 once and 6737 twice: RemoveDois gives it two call
// sites and stands for 7160 and 6737 (1487 is in the link, unit 168).
// CopyFile (target fn 378) is called directly by 15 target functions (1836, 2725, 3333, 4657, 4682, 4687, 5371, 5873,
// 5874, 6737, 7174, 11630, 11631, 11632 and 12098); 5873, 5874, 11630, 11631 and 11632 are in the link (units 160 and
// 122), and so are vota::CSincronizaVota's 1836, 3333, 4657, 4682 and 4687 (fragment 205): CopiaDuas stands for the
// other five. Every target
// caller passes the same value for one of its two bools, which the target's type (i32 i32 i32) has folded, and 0 or 1
// for the other (2725 passes 1, the rest 0): CopiaDuas passes the folded one as 1 at both sites, the other as 0 and 1.
// Rename has no target index of its own: binaryen inlines it into its one caller, fn 11584 (comum::CGravadorLog's slot
// 7, not reconstructed). RenomeiaUma stands for 11584 and calls it once, so binaryen inlines it there too; its code
// then gives the std::format arguments' builder that CopyFile shares (fn 5456) the second caller it has in the target.
// libc's utime (fn 6238) is called by CopyFile and by 7-Zip's fn 2585, which our link does not hold: AjustaHora stands
// for 2585, so binaryen keeps utime out of line as the target does.
// libc's statfs (fn 3972) is called by libc++'s std::filesystem::__space (fn 4677, which GetFreeSpace and GetUsedSpace
// call), through statvfs, and directly by 2725 (comum::CControlaArmazenamentoDeImagens, its records at
// ccontrolaarmazenamentodeimagens.cpp 73 to 152) and 5371 (the "me{:06}.wsq" writer), neither reconstructed: with
// __space its only caller, binaryen inlines it there and __space is not the target's. LivreEmDois stands for 2725 and
// 5371 with one call site each.
// api::RemoveTree (target fn 5458) is called by itself and by 5455 (CSystem::ReplaceFile), both reconstructed.
// CSystem::ReplaceFile (target fn 5455) is called twice by fn 7174 (vota::impl::CSincronismoVotoEleitor's slot 2),
// not reconstructed: RepoeDois stands for it with two call sites, each passing an empty third string as 7174 does.
// api::GetFileName and GetDirName (target fns 2763 and 5462) are called by 1501 (vota::CAssinadorVota's constructor,
// with comum::CAssinador's inlined, reconstructed) once each and by 12098, and GetFileName by 5360 and 5461 too. 5461
// (api::TrocaExtensao, unit 280's fragment) is in the link; 12098 and 5360 are not: PartesDoCaminho stands for them with
// one call site of each.
// The stand-ins' bodies differ, so wasm-opt merges none of them, and no argument is the same constant at every call
// site but CopyFile's folded bool, which the target folds too, so dead-argument elimination folds no other. They are
// address-taken from a static constructor. Declared through asm labels with the wasm-level signatures; compiled as
// uenux2 code.
#include <sys/statfs.h>
#include <utime.h>

extern "C" {
int w2759_root_0(int) __asm__("_ZN3api7CSystem11GetFileSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w412_root_0(int) __asm__("_ZN3api7CSystem9ExistFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w2760_root_0(int) __asm__("_ZN3api7CSystem10RemoveFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w378_root_0(int, int, int, int) __asm__("_ZN3api7CSystem8CopyFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_bb");
void w11584_root_0(int, int) __asm__("_ZN3api7CSystem6RenameERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_");
void w5455_root_0(int, int, int) __asm__("_ZN3api7CSystem11ReplaceFileERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_S9_");
void w2763_root_0(int, int) __asm__("_ZN3api11GetFileNameERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
void w5462_root_0(int, int) __asm__("_ZN3api10GetDirNameERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
int w2762_root_0(int) __asm__("_ZN3api7CSystem10IsEmptyDirERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) int MesmoTamanho(int arquivoA, int arquivoB)
{
    return w2759_root_0(arquivoA) == w2759_root_0(arquivoB);
}

__attribute__((noinline)) int ContaRecursos(int arquivo, int diretorio, int outro)
{
    return w412_root_0(arquivo) + w412_root_0(outro) * 2 + diretorio * 4;
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

__attribute__((noinline)) void RepoeDois(int novoA, int atualA, int novoB, int atualB)
{
    int vazio[3] = {0, 0, 0};
    w5455_root_0(novoA, atualA, reinterpret_cast<int>(vazio));
    w5455_root_0(novoB + 12, atualB, reinterpret_cast<int>(vazio));
}

__attribute__((noinline)) int AjustaHora(const char* arquivo)
{
    return utime(arquivo, nullptr) + 1;
}

__attribute__((noinline)) unsigned long long LivreEmDois(const char* particaoA, const char* particaoB)
{
    struct statfs infoA;
    struct statfs infoB;
    if (statfs(particaoA, &infoA) != 0 || statfs(particaoB, &infoB) != 0) {
        return 0;
    }
    return infoA.f_bavail * infoA.f_bsize + infoB.f_bfree;
}

__attribute__((noinline)) void PartesDoCaminho(int arquivo, int diretorio, int caminho)
{
    w2763_root_0(arquivo, caminho);
    w5462_root_0(diretorio, caminho);
}

__attribute__((noinline)) int DiretorioVazio(int diretorio)
{
    return w2762_root_0(diretorio) + 3;
}

void* volatile w2759_sink;

struct SW2759Roots {
    SW2759Roots()
    {
        w2759_sink = reinterpret_cast<void*>(&MesmoTamanho);
        w2759_sink = reinterpret_cast<void*>(&ContaRecursos);
        w2759_sink = reinterpret_cast<void*>(&RemoveDois);
        w2759_sink = reinterpret_cast<void*>(&w412_root_0);
        w2759_sink = reinterpret_cast<void*>(&CopiaDuas);
        w2759_sink = reinterpret_cast<void*>(&RenomeiaUma);
        w2759_sink = reinterpret_cast<void*>(&AjustaHora);
        w2759_sink = reinterpret_cast<void*>(&LivreEmDois);
        w2759_sink = reinterpret_cast<void*>(&RepoeDois);
        w2759_sink = reinterpret_cast<void*>(&PartesDoCaminho);
        w2759_sink = reinterpret_cast<void*>(&DiretorioVazio);
    }
} w2759_roots;

} // namespace
