// Roots of unit 247: the call sites the target gives the two functions whose one body is target fn 1255, the voter's
// screen of the poll workers' registration (src/units/247-uenux2-cregistrarmesarios.mk). Neither has a target caller in
// the link. binaryen inlines a function with one call site (docs/reference/facts/tool-traps.md X1), and the unit rests
// on each of the two keeping its body until duplicate-function-elimination joins them, so each gets two call sites
// here. Which target callers called which function is chosen (the fragment says so); each stand-in names the ones it
// stands for, and goes when they are in splat/matched.txt or written in the link.
//
// Declared through asm labels with the wasm-level signatures (the std::shared_ptr result is returned through the
// address passed first, ahead of `this`), so this TU needs no uenux2 header and instantiates nothing; compiled as app
// code.
extern "C" {
void w247_tela(void* resultado) __asm__("_ZN5comum20TelaRegistroMesariosEv");
void w247_tela_eleitor(void* resultado, void* estado) __asm__("_ZN5comum18IPedeTituloMesario14GetTelaEleitorEv");
}

namespace {

volatile int w247_n;
alignas(8) char w247_formularios[64];

// Stands for the constructors of the states over comum::CAppState that store fn 1255's form at +20, each inlined into
// the function that holds its GetInst: comum::CRegistrarMesarios's (fn 3610), CConfirmaFimRegistroMesarios's (fn 5389),
// CLimiteMesariosRegistradosAtingido's (fn 5386), CMesarioRegistrado's (fn 10337) and CTituloMesarioVazio's,
// CTituloMesarioInvalido's and CTituloMesarioJaRegistrado's (fn 10313, three call sites).
__attribute__((noinline)) int ConstroiEstadosRegistro(int n)
{
    w247_tela(w247_formularios + (n & 8));
    w247_tela(w247_formularios + 16);
    return n * 3 + 5;
}

// Stands for the constructors of comum::CPedeTituloMesarioInicial, CPedeTituloMesarioFinal and
// CPedeTituloMesarioVotacao, inlined into fn 10388 (three call sites).
__attribute__((noinline)) int ConstroiPedeTituloEstados(int n)
{
    w247_tela_eleitor(w247_formularios + 32, w247_formularios + 48 + (n & 4));
    w247_tela_eleitor(w247_formularios + 40, w247_formularios + 56);
    return n * 7 + 9;
}

struct SW247Roots {
    SW247Roots()
    {
        w247_n = ConstroiEstadosRegistro(w247_n);
        w247_n = ConstroiPedeTituloEstados(w247_n);
    }
} w247_roots;

} // namespace
