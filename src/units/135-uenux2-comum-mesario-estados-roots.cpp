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
// The vtable is declared through an asm label; ReconheceDigital instantiates api::CPolySingleton<
// api::IFingerMatcher>::instance, a landed header's template, whose copy matches from this object (fn 1686). So this
// TU compiles at uenux2's flags for the directory, not APP_CXXFLAGS: no match rests on a flag the tree lacks (the
// fragment has the strict-aliasing measurement).
#include <source_location>

#include "api/hwil/ifingermatcher.h"
#include "api/pattern/cpolysingleton.h"

extern "C" {
extern const char cdigitalmesarionaoreconhecida_vt[] __asm__("_ZTVN5comum29CDigitalMesarioNaoReconhecidaE");
}

namespace {

// Stands for the target callers of api::CPolySingleton<api::IFingerMatcher>::instance (fn 1686) not written: 3614, 5372,
// 10316 (CPedeDigitalMesario::ProcessTick, pending here), 10465 and 10474 (10482, unit 282's, is in the link). It calls the instance twice,
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

struct SMesarioEstadosRoots {
    SMesarioEstadosRoots()
    {
        mesario_estados_sink = reinterpret_cast<const void*>(&ReconheceDigital);
        mesario_estados_sink = cdigitalmesarionaoreconhecida_vt;
    }
} mesario_estados_roots;

} // namespace
