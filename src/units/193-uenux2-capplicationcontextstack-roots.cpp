// Roots of fragment 193: keep api::CApplicationContextStack's and api::CApplicationContext's functions and the two
// factories in the skeleton link the way the target keeps them. Declared through asm labels with the objects'
// signatures (a constructor returns this; a function that returns a class by value takes the result's address first);
// compiled with APP_CXXFLAGS. Each stand-in's body differs from the others' and from every target function.
// - CApplicationContextStack::Pop (fn 5553) has two direct callers in the target, fns 7370 and 10467, neither
//   reconstructed: w193_desempilha stands for them, two call sites on api::CApplication::s_contextos (unit 171), the
//   stack the target's 5553 reads at its address as a constant.
// - api::CriaContextoAplicacao (fn 3682) has api::CApplication::CriaContexto's code among its callers in our link;
//   w193_contexto stands for the other two, fns 2740 and 3229.
// - api::CriaContextoPadrao (fn 5558) has api::CApplication::InitApplication's code among its callers in our link;
//   w193_padrao stands for the other, fn 1695.
// - CApplicationContext's copy constructor (fn 1841) has fn 676's code (the guard's constructor, inlined) among its
//   callers in our link; w193_copia stands for the other five, fns 491, 1695, 3333, 7377 and 10468.
extern "C" {
extern char w193_contextos[] __asm__("_ZN3api12CApplication11s_contextosE");
void w193_desempilha_c(void* pilha, const void* contexto) __asm__(
    "_ZN3api24CApplicationContextStack3PopERKNS_19CApplicationContextE");
void w193_contexto_c(void* contexto, int tipo, void* titulo, void* descricao, void* detalhe) __asm__(
    "_ZN3api21CriaContextoAplicacaoEiNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES6_S6_");
void w193_padrao_c(void* contexto, void* titulo, void* descricao) __asm__(
    "_ZN3api18CriaContextoPadraoENSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES6_");
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

__attribute__((noinline)) int w193_padrao(char* bloco)
{
    w193_padrao_c(bloco + 8, bloco + 60, bloco + 72);
    return bloco[11] ^ 11;
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
        w193_sink = reinterpret_cast<void*>(&w193_padrao);
        w193_sink = reinterpret_cast<void*>(&w193_copia);
    }
} w193_roots;

} // namespace
