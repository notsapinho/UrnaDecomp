// Roots of fragment 171. Declared through asm labels with the objects' signatures (a non-deleting destructor returns
// this; a function that returns a class by value takes the result's address first); compiled with APP_CXXFLAGS. Each
// stand-in's body differs from the others' and from every target function.
// - api::CApplication::EnterLoopDoingNothing (target fn 5566) has two direct callers in the target, 7709 and 7710
//   (slots 4 and 3 of vota::CThreadVota's vtable, which CThreadEleitor, CThreadMonitor and CThreadOperador share),
//   neither reconstructed. AguardaUmaVez and AguardaDuasVezes stand for them, two call sites, so binaryen keeps it out
//   of line.
// - InitApplication (fn 11159) is the table slot main (fn 10307, unit 170) passes to invoke_viiii, so it needs no line
//   here.
// - PushContext (fn 3684) has InitApplication's code among its callers in our link; w171_empilha stands for the other
//   two, fns 7377 and 10468.
// - CriaContexto from a kind and three strings (fn 676) and api::CApplicationContextGuard's destructor (fn 675, unit
//   193) have the same ten direct callers in the target (491 1277 3333 4657 4682 10590 12098 12105 12110 12134), none
//   reconstructed: w171_guarda and w171_guardas stand for them, three call sites of each. The other CriaContexto and
//   the guard's constructor have one caller each and are left unrooted, so binaryen inlines them as the target does.
// - DescreveModo stands for 4620, not reconstructed, the caller of api::CApplication::GetDescricaoModo (fn 5564)
//   beside 502: with 502 alone binaryen would inline 5564 into it.
extern "C" {
void w5566_root_0() __asm__("_ZN3api12CApplication21EnterLoopDoingNothingEv");
void w5564_root_0(void* resultado) __asm__("_ZN3api12CApplication16GetDescricaoModoEv");
void w171_empilha_c(void* contexto) __asm__("_ZN3api12CApplication11PushContextENS_19CApplicationContextE");
void w171_guarda_c(void* guarda, int tipo, void* titulo, void* descricao, void* detalhe) __asm__(
    "_ZN3api12CApplication12CriaContextoEiNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES7_S7_");
int w171_guarda_d(void* guarda) __asm__("_ZN3api24CApplicationContextGuardD1Ev");
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

__attribute__((noinline)) int w171_empilha(char* bloco)
{
    w171_empilha_c(bloco + 20);
    return bloco[7] - 1;
}

__attribute__((noinline)) int w171_guarda(char* bloco, int tipo)
{
    w171_guarda_c(bloco, tipo, bloco + 56, bloco + 68, bloco + 80);
    w171_guarda_d(bloco);
    return bloco[3] + 3;
}

__attribute__((noinline)) int w171_guardas(char* bloco)
{
    w171_guarda_c(bloco, 4, bloco + 60, bloco + 72, bloco + 84);
    w171_guarda_c(bloco + 96, 9, bloco + 152, bloco + 164, bloco + 176);
    w171_guarda_d(bloco + 96);
    w171_guarda_d(bloco);
    return bloco[5] * 5;
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
        w5566_sink = reinterpret_cast<void*>(&w171_empilha);
        w5566_sink = reinterpret_cast<void*>(&w171_guarda);
        w5566_sink = reinterpret_cast<void*>(&w171_guardas);
        w5566_sink = reinterpret_cast<void*>(&DescreveModo);
    }
} w5566_roots;

} // namespace
