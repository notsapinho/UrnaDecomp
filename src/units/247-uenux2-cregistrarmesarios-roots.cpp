// Roots of unit 247: the call site the target gives comum::CRegistrarMesarios::GetInst (fn 3610)
// (src/units/247-uenux2-cregistrarmesarios.mk). binaryen inlines a function with one call site
// (docs/reference/facts/tool-traps.md X1). The unit rests on each of the two screen functions whose one body is target
// fn 1255 keeping its body until duplicate-function-elimination joins them; both have their callers in the link now
// (TelaRegistroMesarios the constructors in fns 3610, 5386, 5389, 10313 and 10337, comum::TelaEleitorRegistroMesarios
// the three constructors fn 10388 holds; which target callers called which function is chosen, ipedetitulomesario.h
// says what the bytes decide),
// so they need no stand-in. GetInst has one caller written, fn 10737, and gets one call here. A stand-in names the
// target callers it stands for, and goes when they are all in splat/matched.txt or written in the link.
//
// Declared through an asm label with the wasm-level signature, so this TU needs no uenux2 header and instantiates
// nothing; compiled as app code.
extern "C" {
int w247_registrar(void) __asm__("_ZN5comum18CRegistrarMesarios7GetInstEv");
}

namespace {

volatile int w247_n;

// Stands for the target's other caller of comum::CRegistrarMesarios::GetInst (fn 3610) not in the link,
// vota::CEscolheOpcao::ProcessInput (fn 10689); vota::CAguardaInicio's slot 6 (fn 10217, unit 165's) is in the link.
__attribute__((noinline)) int ChamaRegistrarMesarios(int n)
{
    return w247_registrar() + n * 11;
}

struct SW247Roots {
    SW247Roots()
    {
        w247_n = ChamaRegistrarMesarios(w247_n);
    }
} w247_roots;

} // namespace
