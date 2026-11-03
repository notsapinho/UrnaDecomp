// Roots of fragment 171. Declared through asm labels with the objects' signatures (a non-deleting destructor returns
// this; a function that returns a class by value takes the result's address first); compiled with APP_CXXFLAGS. Each
// stand-in's body differs from the others' and from every target function.
// - api::CApplication::EnterLoopDoingNothing (target fn 5566) has two direct callers in the target, 7709 and 7710
//   (slots 4 and 3 of vota::CThreadVota's vtable, which CThreadEleitor, CThreadMonitor and CThreadOperador share),
//   neither reconstructed. AguardaUmaVez and AguardaDuasVezes stand for them, two call sites, so binaryen keeps it out
//   of line.
// - InitApplication (fn 11159) is the table slot main (fn 10307, unit 170) passes to invoke_viiii, so it needs no line
//   here.
// - PushContext (fn 3684) has InitApplication's code and unit 197's StartState (fn 7377) among its callers in our link;
//   w171_empilha stands for the other, fn 10468.
// - CriaContexto from a kind and three strings (fn 676) and api::CApplicationContextGuard's destructor (fn 675, unit
//   193) have the same ten direct callers in the target (491 1277 3333 4657 4682 10590 12098 12105 12110 12134), of
//   which 1277 (comum::CAssinador::Assina, unit 34), 4657 and 4682 (unit 205) are reconstructed: w171_guarda and
//   w171_guardas stand for the other seven, three call sites of each. The other CriaContexto and
//   the guard's constructor have one caller each and are left unrooted, so binaryen inlines them as the target does.
// - GetContexto (fn 1695) has seven direct calls in the target: GetExceptionLevel's (fn 5569, in the link) and three
//   each in 7709 and 7710 (vota::CThreadVota's two TrataErro, traps in unit 116's pending file); w171_contexto stands
//   for those two. GetExceptionLevel's two callers are 7709 and 7710, which w171_nivel stands for, and so are two of
//   api::Join's (fn 1696) five; w171_junta stands for four (5604, 7709, 7710, 11233; 652, unit 161's, is in the link).
extern "C" {
void w5566_root_0() __asm__("_ZN3api12CApplication21EnterLoopDoingNothingEv");
void w171_empilha_c(void* contexto) __asm__("_ZN3api12CApplication11PushContextENS_19CApplicationContextE");
void w171_guarda_c(void* guarda, int tipo, void* titulo, void* descricao, void* detalhe) __asm__(
    "_ZN3api12CApplication12CriaContextoEiNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES7_S7_");
int w171_guarda_d(void* guarda) __asm__("_ZN3api24CApplicationContextGuardD1Ev");
void w1695_root(void* resultado) __asm__("_ZN3api12CApplication11GetContextoEv");
int w5569_root() __asm__("_ZN3api17GetExceptionLevelEv");
void w1696_root(void* resultado, void* partes, void* separador) __asm__(
    "_ZN3api4JoinERKNSt3__26vectorINS0_12basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEENS5_IS7_EEEERKS7_");
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

// stands for fns 7709 and 7710
__attribute__((noinline)) int w171_contexto(char* bloco)
{
    w1695_root(bloco + 8);
    return bloco[51] + 7;
}

// stands for fns 7709 and 7710
__attribute__((noinline)) int w171_nivel(int a)
{
    return w5569_root() * 3 + w5569_root() + a;
}

// stands for fns 5604, 7709, 7710 and 11233 (652 is in the link)
__attribute__((noinline)) int w171_junta(char* bloco)
{
    w1696_root(bloco, bloco + 12, bloco + 24);
    w1696_root(bloco + 36, bloco + 12, bloco + 48);
    return bloco[47] - 2;
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
        w5566_sink = reinterpret_cast<void*>(&w171_contexto);
        w5566_sink = reinterpret_cast<void*>(&w171_nivel);
        w5566_sink = reinterpret_cast<void*>(&w171_junta);
    }
} w5566_roots;

} // namespace
