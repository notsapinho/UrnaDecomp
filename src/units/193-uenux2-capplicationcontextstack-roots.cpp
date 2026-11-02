// Roots of fragment 193: keep api::CApplicationContextStack's and api::CApplicationContext's functions and the two
// factories in the skeleton link the way the target keeps them. Declared through asm labels with the objects'
// signatures (a constructor returns this; a function that returns a class by value takes the result's address first);
// compiled with APP_CXXFLAGS. Each stand-in's body differs from the others' and from every target function.
// - CApplicationContextStack::Pop (fn 5553) has two direct callers in the target, fns 7370 and 10467: 7370,
//   vota::CEleitorVotando::FinishState (unit 197), is in the link, and w193_desempilha stands for 10467, two call
//   sites on api::CApplication::s_contextos (unit 171), the stack the target's 5553 reads at its address as a constant.
// - api::CriaContextoAplicacao (fn 3682) has api::CApplication::CriaContexto's code among its callers in our link, and
//   vota::CEleitorVotando::GetInst (fn 3229, unit 197); w193_contexto stands for the other, fn 2740.
// - api::CriaContextoPadrao (fn 5558) needs no stand-in: its two target callers, api::CApplication::InitApplication's
//   code and GetContexto (fn 1695, unit 171), are in the link.
// - CApplicationContext's copy constructor (fn 1841) has fn 676's code (the guard's constructor, inlined) among its
//   callers in our link, unit 197's StartState (7377) and GetContexto (1695, unit 171); w193_copia stands for the
//   other three, fns 491, 3333 and 10468.
extern "C" {
extern char w193_contextos[] __asm__("_ZN3api12CApplication11s_contextosE");
void w193_desempilha_c(void* pilha, const void* contexto) __asm__(
    "_ZN3api24CApplicationContextStack3PopERKNS_19CApplicationContextE");
void w193_contexto_c(void* contexto, int tipo, void* titulo, void* descricao, void* detalhe) __asm__(
    "_ZN3api21CriaContextoAplicacaoEiNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES6_S6_");
int w193_copia_c(void* contexto, const void* outro) __asm__("_ZN3api19CApplicationContextC2ERKS0_");
}

namespace {

__attribute__((noinline)) int w193_desempilha(char* bloco)
{
    w193_desempilha_c(w193_contextos, bloco + 20);
    w193_desempilha_c(w193_contextos, bloco + 32);
    return bloco[3] * 9;
}

__attribute__((noinline)) int w193_contexto(char* bloco, int tipo)
{
    w193_contexto_c(bloco, tipo + 2, bloco + 52, bloco + 64, bloco + 76);
    return bloco[7] - 7;
}

__attribute__((noinline)) int w193_copia(char* bloco)
{
    w193_copia_c(bloco + 52, bloco);
    return bloco[13] + 13;
}

void* volatile w193_sink;

struct SW193Roots {
    SW193Roots()
    {
        w193_sink = reinterpret_cast<void*>(&w193_desempilha);
        w193_sink = reinterpret_cast<void*>(&w193_contexto);
        w193_sink = reinterpret_cast<void*>(&w193_copia);
    }
} w193_roots;

} // namespace
