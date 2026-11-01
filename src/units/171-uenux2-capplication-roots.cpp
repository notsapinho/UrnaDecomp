// Roots of fragment 171: api::CApplication::EnterLoopDoingNothing (target fn 5566) has two direct callers in the target,
// 7709 and 7710 (slots 4 and 3 of vota::CThreadVota's vtable, which CThreadEleitor, CThreadMonitor and CThreadOperador
// share), neither reconstructed. AguardaUmaVez and AguardaDuasVezes stand for them, two call sites, so binaryen keeps it
// out of line; their bodies differ from each other and from every target function. DescreveModo stands for 4620, not
// reconstructed, the caller of api::CApplication::GetDescricaoModo (fn 5564) beside 502: with 502 alone binaryen would
// inline 5564 into it. Declared through asm labels with the object's signatures (5564's std::string result through its
// address); compiled with APP_CXXFLAGS.
extern "C" {
void w5566_root_0() __asm__("_ZN3api12CApplication21EnterLoopDoingNothingEv");
void w5564_root_0(void* resultado) __asm__("_ZN3api12CApplication16GetDescricaoModoEv");
}

namespace {

__attribute__((noinline)) int AguardaUmaVez(int a)
{
    w5566_root_0();
    return a + 3;
}

__attribute__((noinline)) int AguardaDuasVezes(int a)
{
    w5566_root_0();
    w5566_root_0();
    return a * 5;
}

__attribute__((noinline)) int DescreveModo(int a)
{
    alignas(4) char texto[12];
    w5564_root_0(texto);
    return a + texto[11];
}

void* volatile w5566_sink;

struct SW5566Roots {
    SW5566Roots()
    {
        w5566_sink = reinterpret_cast<void*>(&AguardaUmaVez);
        w5566_sink = reinterpret_cast<void*>(&AguardaDuasVezes);
        w5566_sink = reinterpret_cast<void*>(&DescreveModo);
    }
} w5566_roots;

} // namespace
