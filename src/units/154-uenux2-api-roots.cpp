// Roots of fragment 154.
// - api::KeyName(char) (target fn 744), an inline function of api/hwil/iinput.h: the target calls it directly from five
//   functions (653, 1455, 2243, 7787 and 12903), none reconstructed yet, and its copy reads as
//   cinstrucaovotacaoacessibilidade.cpp's (its record, 1533820, follows that file's records). TamanhoDoNome and
//   SomaDosNomes call it, so this object emits the copy; they are optnone, so that clang does not inline it into them, and
//   they give it two call sites, so binaryen keeps it out of line. This object compiles at the uenux2 tree's flags (the
//   fragment's rule), so its copy is compiled as the tree's own users compile theirs.
// - api::CSynchronizer::GetInst (target fn 600) is called directly by 14 target functions (378, 491, 1487 and others),
//   none reconstructed yet: InstanciaDuasVezes calls it twice. Its constructor (fn 5729) has two callers in the
//   target, 600 and 6652 (not reconstructed): Constroi stands for 6652, so that binaryen keeps the constructor out of
//   line beside GetInst's call. Both are declared through asm labels, the constructor with the object's int result.
// The stand-ins' bodies differ from each other and from every target function.
#include "api/hwil/iinput.h"

extern "C" {
int w600_root_0() __asm__("_ZN3api13CSynchronizer7GetInstEv");
int w5729_root_0(int, int) __asm__("_ZN3api13CSynchronizerC1Eb");
}

namespace {

__attribute__((optnone, noinline)) unsigned TamanhoDoNome(char tecla)
{
    return api::KeyName(tecla).size();
}

__attribute__((optnone, noinline)) unsigned SomaDosNomes(char teclaA, char teclaB)
{
    return api::KeyName(teclaA).size() * 2 + api::KeyName(teclaB).size();
}

__attribute__((noinline)) int InstanciaDuasVezes()
{
    return w600_root_0() - w600_root_0();
}

__attribute__((noinline)) int Constroi(int objeto, int habilitado)
{
    return w5729_root_0(objeto + 4, habilitado != 0);
}

void* volatile w154_sink;

struct SW154Roots {
    SW154Roots()
    {
        w154_sink = reinterpret_cast<void*>(&TamanhoDoNome);
        w154_sink = reinterpret_cast<void*>(&SomaDosNomes);
        w154_sink = reinterpret_cast<void*>(&InstanciaDuasVezes);
        w154_sink = reinterpret_cast<void*>(&Constroi);
    }
} w154_roots;

} // namespace
