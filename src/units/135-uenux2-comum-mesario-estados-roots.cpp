// Roots: keep the vtables of comum's mesario states whose constructor is not reconstructed
// (src/units/135-uenux2-comum-mesario-estados.mk) in the skeleton link the way the target keeps them.
//
// In the target each vtable is referenced only by its class's constructor, inlined with GetInst into the function that
// stores the vptr (`/usr/bin/grep -rlE 'i32\.const <vptr>($|[^0-9])' build/out/splat/pieces/asm`): fns 5389 and 5386
// for CConfirmaFimRegistroMesarios and CLimiteMesariosRegistradosAtingido, fn 10313 (IPedeTituloMesario::ProcessInput)
// for CTituloMesarioVazio, CTituloMesarioInvalido, CTituloMesarioJaRegistrado and CPedeDigitalMesario, fn 10316
// (CPedeDigitalMesario::ProcessTick) for CDigitalMesarioNaoReconhecida. None of those is written. Rooting the vtable
// keeps every slot in the table, which is how the target reaches StartState and ProcessInput. CEncerraRegistroMesarios
// needs no root: its constructor is written, inlined into GetInst (fn 5388), which the two ProcessInput slots that end
// the registration call.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cconfirmafimregistromesarios_vt[] __asm__("_ZTVN5comum28CConfirmaFimRegistroMesariosE");
extern const char climitemesariosregistradosatingido_vt[] __asm__("_ZTVN5comum34CLimiteMesariosRegistradosAtingidoE");
extern const char ctitulomesariovazio_vt[] __asm__("_ZTVN5comum19CTituloMesarioVazioE");
extern const char ctitulomesarioinvalido_vt[] __asm__("_ZTVN5comum22CTituloMesarioInvalidoE");
extern const char ctitulomesariojaregistrado_vt[] __asm__("_ZTVN5comum26CTituloMesarioJaRegistradoE");
extern const char cdigitalmesarionaoreconhecida_vt[] __asm__("_ZTVN5comum29CDigitalMesarioNaoReconhecidaE");
extern const char cpededigitalmesario_vt[] __asm__("_ZTVN5comum19CPedeDigitalMesarioE");
}

namespace {

const void* volatile mesario_estados_sink;

struct SMesarioEstadosRoots {
    SMesarioEstadosRoots()
    {
        mesario_estados_sink = cconfirmafimregistromesarios_vt;
        mesario_estados_sink = climitemesariosregistradosatingido_vt;
        mesario_estados_sink = ctitulomesariovazio_vt;
        mesario_estados_sink = ctitulomesarioinvalido_vt;
        mesario_estados_sink = ctitulomesariojaregistrado_vt;
        mesario_estados_sink = cdigitalmesarionaoreconhecida_vt;
        mesario_estados_sink = cpededigitalmesario_vt;
    }
} mesario_estados_roots;

} // namespace
