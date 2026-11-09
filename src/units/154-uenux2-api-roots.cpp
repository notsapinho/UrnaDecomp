// Roots of fragment 154.
// - api::KeyName(char) (target fn 744), an inline function of api/hwil/iinput.h: the target calls it directly from five
//   functions (653, 1455, 2243, 7787 and 12903), of which 2243 (api::CFormBuilder::AddLabeledKey, unit 31), 1455
//   (vota::CVotacaoStateAudio::PlayKey, unit 97), 653 (api::CInteractiveFormBuilder::AddLabeledInputControl, unit
//   120) and 12903 (the keyboard test's failure text, a lambda of unit 110's ctelasvota.cpp, two calls) are
//   reconstructed, and its copy reads as
//   cinstrucaovotacaoacessibilidade.cpp's (its record, 1533820, follows that file's records). TamanhoDoNome calls it
//   and stands for 7787; it is optnone, so that clang does not inline it there. SomaDosNomes, which stood for 12903 with
//   two calls, went. The copy the
//   link keeps is ctelasvota.cpp.o's, the first in link order (the scan's object column). This object compiles at the
//   uenux2 tree's flags (the fragment's rule), so its copy is compiled as the tree's own users compile theirs, but for
//   -fno-strict-aliasing, which app/vota/'s objects drop (src/Makefile UENUX2_TBAA_DIRS): 744's body is the same
//   without it (wasm-objdump -d of the object compiled both ways).
// - api::CSynchronizer::GetInst (target fn 600) is called directly by 14 target functions (378, 491, 1487 and others):
//   CSystem::CopyFile (378, unit 32), vota::CSincronizaVota's SincronizaRelatorios and GravaBancoDadosMI (1836, 4657,
//   unit 205), 1487 and 1488 (vota/comum/votadefs.cpp, unit 168), 491 and 3333 (SincronizaEstadoGeralVota and
//   SincronizaEstadoGeral, unit 205), 10590 (unit 283), 12105 (fragment 372), 6737 (unit 116) and 7174 (unit 241) are
//   reconstructed, and InstanciaDuasVezes, which calls it twice, stands for the other 3 (12098, 12110 and 12134).
// - CSynchronizer::Sync (target fn 620) is called directly by 14 target functions (378, 491, 1487, 1488, 1836, 3333,
//   4657, 6737, 7174, 10590, 12098, 12105, 12110 and 12134): CopyFile (378), 491, 1487, 1488, 1836, 3333, 4657,
//   6737, 7174, 10590 and 12105 are reconstructed, and SincronizaDuas stands for the other 3 with two call sites, so
//   binaryen keeps Sync out of line as the target does. Its constructor (fn 5729, one body with
//   comum::CRespostasDSNumero's, whose name the match list gives it) has two callers in the target, 600 and 6652
//   (vota's adicionaBaseTelaCompletaConsulta, unit 441's), both in the link: Constroi, which stood for 6652, went.
//   Both are declared through asm labels.
// The stand-ins' bodies differ from each other and from every target function.
#include "api/hwil/iinput.h"

extern "C" {
int w600_root_0() __asm__("_ZN3api13CSynchronizer7GetInstEv");
void w620_root_0(int) __asm__("_ZNK3api13CSynchronizer4SyncEv");
}

namespace {

__attribute__((optnone, noinline)) unsigned TamanhoDoNome(char tecla)
{
    return api::KeyName(tecla).size();
}


__attribute__((noinline)) int InstanciaDuasVezes()
{
    return w600_root_0() - w600_root_0();
}

__attribute__((noinline)) void SincronizaDuas(int sincronizadorA, int sincronizadorB)
{
    w620_root_0(sincronizadorA);
    w620_root_0(sincronizadorB + 8);
}

void* volatile w154_sink;

struct SW154Roots {
    SW154Roots()
    {
        w154_sink = reinterpret_cast<void*>(&TamanhoDoNome);
        w154_sink = reinterpret_cast<void*>(&InstanciaDuasVezes);
        w154_sink = reinterpret_cast<void*>(&SincronizaDuas);
    }
} w154_roots;

} // namespace
