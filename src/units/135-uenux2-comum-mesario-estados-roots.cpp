// Roots: keep the vtables of comum's mesario states whose constructor is not reconstructed
// (src/units/135-uenux2-comum-mesario-estados.mk) in the skeleton link the way the target keeps them.
//
// In the target each vtable is referenced only by its class's constructor, inlined with GetInst into the function that
// stores the vptr (`/usr/bin/grep -rlE 'i32\.const <vptr>($|[^0-9])' build/out/splat/pieces/asm`): fn 5389 for
// CConfirmaFimRegistroMesarios, fn 10313 (IPedeTituloMesario::ProcessInput) for CTituloMesarioVazio,
// CTituloMesarioInvalido, CTituloMesarioJaRegistrado and CPedeDigitalMesario, fn 10316
// (CPedeDigitalMesario::ProcessTick) for CDigitalMesarioNaoReconhecida. None of those is written. Rooting the vtable
// keeps every slot in the table, which is how the target reaches StartState and ProcessInput. CEncerraRegistroMesarios
// needs no root: its constructor is written, inlined into GetInst (fn 5388), which the two ProcessInput slots that end
// the registration call. Nor does CLimiteMesariosRegistradosAtingido: its constructor is written, inlined into GetInst
// (fn 5386), which comum::CRegistrarMesarios::StartState (fn 10392, unit 247) calls.
//
// CLimiteMesariosRegistradosAtingido::GetInst (fn 5386) has two direct callers in the target, 10392 (written) and
// comum::CMesarioRegistrado::StartState (fn 10339, not written), and binaryen inlines a function with one call site
// (docs/reference/facts/tool-traps.md X1): ChamaLimiteMesarios stands for 10339 and goes when it is in the link.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cconfirmafimregistromesarios_vt[] __asm__("_ZTVN5comum28CConfirmaFimRegistroMesariosE");
extern const char ctitulomesariovazio_vt[] __asm__("_ZTVN5comum19CTituloMesarioVazioE");
extern const char ctitulomesarioinvalido_vt[] __asm__("_ZTVN5comum22CTituloMesarioInvalidoE");
extern const char ctitulomesariojaregistrado_vt[] __asm__("_ZTVN5comum26CTituloMesarioJaRegistradoE");
extern const char cdigitalmesarionaoreconhecida_vt[] __asm__("_ZTVN5comum29CDigitalMesarioNaoReconhecidaE");
extern const char cpededigitalmesario_vt[] __asm__("_ZTVN5comum19CPedeDigitalMesarioE");
int w135_limite(void) __asm__("_ZN5comum34CLimiteMesariosRegistradosAtingido7GetInstEv");
}

namespace {

const void* volatile mesario_estados_sink;
volatile int w135_n;

__attribute__((noinline)) int ChamaLimiteMesarios(int n)
{
    return w135_limite() + n * 13;
}

struct SMesarioEstadosRoots {
    SMesarioEstadosRoots()
    {
        mesario_estados_sink = cconfirmafimregistromesarios_vt;
        mesario_estados_sink = ctitulomesariovazio_vt;
        mesario_estados_sink = ctitulomesarioinvalido_vt;
        mesario_estados_sink = ctitulomesariojaregistrado_vt;
        mesario_estados_sink = cdigitalmesarionaoreconhecida_vt;
        mesario_estados_sink = cpededigitalmesario_vt;
        w135_n = ChamaLimiteMesarios(w135_n);
    }
} mesario_estados_roots;

} // namespace
