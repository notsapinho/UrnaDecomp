// Roots of fragment 291: keep comum::CEleitores::GetCurrentBiometriaEleitor (fn 1393, unit 110's celeitores.cpp) in
// the skeleton link the way the target reaches it: six direct callers (fns 10425, 10465, 10474, 10478, 10500 and
// 10512, vota's identification states; 10465, 10474, 10478, 10500 and 10512 are in the link, units 282, 239 and 161),
// each passing CEleitores::GetInst()'s result. The stand-in is for the other one, 10425. binaryen
// inlines a function called once, so the stand-in calls it twice, on two objects, and reads both 40-byte results.
// Declared through an asm label with the object's signature (the md::CBiometriaEleitor comes back through the result's
// address); the results are left undestroyed: nothing calls the stand-in.
//
// DetectaDigital instantiates api::CPolySingleton<api::IFingerDetection>::instance, a landed header's template, whose
// copy is fn 3615 (its records cpolysingleton.h:78 and cpolysingletonlist.h:99 and :105 name it): of its three target
// callers, fns 10316, 10451 and 10465, 10465 and 10316 (units 282 and 135) are in the link; it calls the instance
// once, for 10451, with an empty std::source_location where the callers' default argument makes a record of their own
// (unit 135's ReconheceDigital, for IFingerMatcher's 1686, does the same). The call that stood for 10316 went. So this
// TU compiles at uenux2's flags, as unit 135's roots do, not APP_CXXFLAGS (the fragment has the strict-aliasing
// measurement).
#include <source_location>

#include "api/hwil/ifingerdetection.h"
#include "api/pattern/cpolysingleton.h"

extern "C" {
void w1393_root(void*, int) __asm__("_ZNK5comum10CEleitores26GetCurrentBiometriaEleitorEv");
}

namespace {

__attribute__((noinline)) int BiometriasCorrentes(int eleitores, int outros)
{
    int biometrias[20];
    w1393_root(biometrias, eleitores);
    w1393_root(biometrias + 10, outros + 4);
    return biometrias[8] - biometrias[18];
}

__attribute__((noinline)) const void* DetectaDigital()
{
    const std::source_location local;
    return &api::CPolySingleton<api::IFingerDetection>::instance(api::g_polySingletonsInfo(), local);
}

const void* volatile biometria_291_sink;

struct SBiometria291Roots {
    SBiometria291Roots()
    {
        biometria_291_sink = reinterpret_cast<const void*>(&BiometriasCorrentes);
        biometria_291_sink = reinterpret_cast<const void*>(&DetectaDigital);
    }
} biometria_291_roots;

} // namespace
