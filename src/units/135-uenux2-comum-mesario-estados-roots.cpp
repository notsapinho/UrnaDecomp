// Roots: keep comum's mesario states (src/units/135-uenux2-comum-mesario-estados.mk) in the skeleton link the way the
// target keeps them, until their callers land.
//
// In the target each vtable is referenced only by its class's constructor, inlined with GetInst into the function that
// stores the vptr (`/usr/bin/grep -rlE 'i32\.const <vptr>($|[^0-9])' build/out/splat/pieces/asm`): fns 5389 and 5386
// for CConfirmaFimRegistroMesarios and CLimiteMesariosRegistradosAtingido, fn 10313 (IPedeTituloMesario::ProcessInput)
// for CTituloMesarioVazio, CTituloMesarioInvalido, CTituloMesarioJaRegistrado and CPedeDigitalMesario, fn 10316
// (CPedeDigitalMesario::ProcessTick) for CDigitalMesarioNaoReconhecida. 5389, 5386, 10313 and 10316 are written and in
// the link, so no vtable is rooted here: their constructors keep every slot in the table, which is how the target
// reaches the states' StartState and ProcessInput. CEncerraRegistroMesarios needs no root: its constructor is written,
// inlined into GetInst (fn 5388), which the two ProcessInput slots that end the registration call.
//
// ReconheceDigital instantiates api::CPolySingleton<api::IFingerMatcher>::instance, a landed header's template, whose
// copy (fn 1686) the link takes from an earlier object now (cpededigitalmesario.cpp.o, at the same flags). This TU
// compiles at uenux2's flags for the directory, not APP_CXXFLAGS: no match rests on a flag the tree lacks (the fragment
// has the strict-aliasing measurement).
#include <source_location>

#include "api/hwil/ifingermatcher.h"
#include "api/pattern/cpolysingleton.h"

namespace {

// Stands for the target callers of api::CPolySingleton<api::IFingerMatcher>::instance (fn 1686) not written: 3614 and
// 5372 (10316, 10465, 10474 and 10482, units 135 and 282, are in the link). It calls the instance twice, so the copy
// stays out of line, with an empty std::source_location where the callers' default argument makes a record of their
// own (unit 100's w100_usa does the same).
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
    }
} mesario_estados_roots;

} // namespace
