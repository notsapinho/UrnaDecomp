// Roots of unit 247: the call sites the target gives the two functions whose one body is target fn 1255, the voter's
// screen of the poll workers' registration, and comum::CRegistrarMesarios::GetInst (fn 3610)
// (src/units/247-uenux2-cregistrarmesarios.mk). binaryen inlines a function with one call site
// (docs/reference/facts/tool-traps.md X1). The unit rests on each of the two screen functions keeping its body until
// duplicate-function-elimination joins them, so each gets two call sites here; which target callers called which
// function is chosen (the fragment says so). GetInst has one caller written, fn 10737, and gets one call here. Each
// stand-in names the target callers it stands for, and goes when they are all in splat/matched.txt or written in the
// link.
//
// Declared through asm labels with the wasm-level signatures (the std::shared_ptr result is returned through the
// address passed first, ahead of `this`), so this TU needs no uenux2 header and instantiates nothing; compiled as app
// code.
extern "C" {
void w247_tela(void* resultado) __asm__("_ZN5comum20TelaRegistroMesariosEv");
void w247_tela_eleitor(void* resultado, void* estado) __asm__("_ZN5comum18IPedeTituloMesario14GetTelaEleitorEv");
int w247_registrar(void) __asm__("_ZN5comum18CRegistrarMesarios7GetInstEv");
}

namespace {

volatile int w247_n;
alignas(8) char w247_formularios[64];

// Stands for the constructors of the states over comum::CAppState that store fn 1255's form at +20, each inlined into
// the function that holds its GetInst, that still wait: CMesarioRegistrado's (fn 10337). comum::CRegistrarMesarios's
// (fn 3610) and CLimiteMesariosRegistradosAtingido's (fn 5386), written here and in unit 135, and
// CConfirmaFimRegistroMesarios's (fn 5389) and CTituloMesarioVazio's, CTituloMesarioInvalido's and
// CTituloMesarioJaRegistrado's (fn 10313, three call sites), in units 135 and 71, are in the link.
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

// Stands for the target's other callers of comum::CRegistrarMesarios::GetInst (fn 3610): vota::CAguardaInicio's slot 6
// (fn 10217) and vota::CEscolheOpcao::ProcessInput (fn 10689).
__attribute__((noinline)) int ChamaRegistrarMesarios(int n)
{
    return w247_registrar() + n * 11;
}

struct SW247Roots {
    SW247Roots()
    {
        w247_n = ConstroiEstadosRegistro(w247_n);
        w247_n = ConstroiPedeTituloEstados(w247_n);
        w247_n = ChamaRegistrarMesarios(w247_n);
    }
} w247_roots;

} // namespace
