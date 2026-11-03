// Roots: keep comum's mesario states (src/units/135-uenux2-comum-mesario-estados.mk) in the skeleton link the way the
// target keeps them, until their callers land.
//
// In the target each vtable is referenced only by its class's constructor, inlined with GetInst into the function that
// stores the vptr (`/usr/bin/grep -rlE 'i32\.const <vptr>($|[^0-9])' build/out/splat/pieces/asm`): fns 5389 and 5386
// for CConfirmaFimRegistroMesarios and CLimiteMesariosRegistradosAtingido, fn 10313 (IPedeTituloMesario::ProcessInput)
// for CTituloMesarioVazio, CTituloMesarioInvalido, CTituloMesarioJaRegistrado and CPedeDigitalMesario, fn 10316
// (CPedeDigitalMesario::ProcessTick) for CDigitalMesarioNaoReconhecida. 5389, 5386 and 10313 are written and in the
// link, so only CDigitalMesarioNaoReconhecida's vtable is rooted here: that keeps every slot in the table, which is how
// the target reaches StartState and ProcessInput. CEncerraRegistroMesarios needs no root: its constructor is written,
// inlined into GetInst (fn 5388), which the two ProcessInput slots that end the registration call.
//
// CLimiteMesariosRegistradosAtingido::GetInst (fn 5386) has two direct callers in the target, 10392 (written) and
// comum::CMesarioRegistrado::StartState (fn 10339, not written), and binaryen inlines a function with one call site
// (docs/reference/facts/tool-traps.md X1): ChamaLimiteMesarios stands for 10339 and goes when it is in the link.
//
// The vtables and 5389 are declared through asm labels; ReconheceDigital instantiates api::CPolySingleton<
// api::IFingerMatcher>::instance, a landed header's template, whose copy matches from this object (fn 1686). So this
// TU compiles at uenux2's flags for the directory, not APP_CXXFLAGS: no match rests on a flag the tree lacks (the
// fragment has the strict-aliasing measurement).
#include <source_location>

#include "api/hwil/ifingermatcher.h"
#include "api/pattern/cpolysingleton.h"

extern "C" {
extern const char cdigitalmesarionaoreconhecida_vt[] __asm__("_ZTVN5comum29CDigitalMesarioNaoReconhecidaE");
int w5389_GetInst() __asm__("_ZN5comum28CConfirmaFimRegistroMesarios7GetInstEv");
int w135_limite(void) __asm__("_ZN5comum34CLimiteMesariosRegistradosAtingido7GetInstEv");
}

namespace {

// Stands for fn 6011, binaryen's shared body of CRegistrarMesarios's and CMesarioRegistrado's ProcessInput (fns 10391 and
// 10338), the other caller of CConfirmaFimRegistroMesarios::GetInst (fn 5389): it stores the result as the next state.
__attribute__((noinline)) int ConfirmaFimRegistro(int estado)
{
    return w5389_GetInst() + estado;
}

// Stands for the target callers of api::CPolySingleton<api::IFingerMatcher>::instance (fn 1686), none of them written:
// 3614, 5372, 10316 (CPedeDigitalMesario::ProcessTick, pending here), 10465, 10474 and 10482. It calls the instance twice,
// so the copy stays out of line, with an empty std::source_location where the callers' default argument makes a record of
// their own (unit 100's w100_usa does the same).
__attribute__((noinline)) int ReconheceDigital()
{
    const std::source_location local;
    api::IFingerMatcher& a = api::CPolySingleton<api::IFingerMatcher>::instance(api::g_polySingletonsInfo(), local);
    api::IFingerMatcher& b = api::CPolySingleton<api::IFingerMatcher>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 9 : 11;
}

const void* volatile mesario_estados_sink;
volatile int w135_n;

__attribute__((noinline)) int ChamaLimiteMesarios(int n)
{
    return w135_limite() + n * 13;
}

struct SMesarioEstadosRoots {
    SMesarioEstadosRoots()
    {
        mesario_estados_sink = reinterpret_cast<const void*>(&ConfirmaFimRegistro);
        mesario_estados_sink = reinterpret_cast<const void*>(&ReconheceDigital);
        mesario_estados_sink = cdigitalmesarionaoreconhecida_vt;
        w135_n = ChamaLimiteMesarios(w135_n);
    }
} mesario_estados_roots;

} // namespace
