// Roots of fragment 291. comum::CEleitores::GetCurrentBiometriaEleitor (fn 1393, unit 110's celeitores.cpp) needs no
// stand-in now: its six direct callers (fns 10425, 10465, 10474, 10478, 10500 and 10512, vota's identification states)
// are in the link, units 142, 282, 239 and 161, and the one that stood for 10425 went.
//
// DetectaDigital instantiates api::CPolySingleton<api::IFingerDetection>::instance, a landed header's template, whose
// copy is fn 3615 (its records cpolysingleton.h:78 and cpolysingletonlist.h:99 and :105 name it): of its three target
// callers, fns 10316, 10451 and 10465, 10465 and 10316 (units 282 and 135) are in the link; it calls the instance
// twice, with an empty std::source_location where the callers' default argument makes a record of their own (unit 135's
// ReconheceDigital, for IFingerMatcher's 1686, does the same). So this TU compiles at uenux2's flags, as unit 135's
// roots do, not APP_CXXFLAGS (the fragment has the strict-aliasing measurement).
#include <source_location>

#include "api/hwil/ifingerdetection.h"
#include "api/pattern/cpolysingleton.h"

namespace {

__attribute__((noinline)) int DetectaDigital()
{
    const std::source_location local;
    api::IFingerDetection& a = api::CPolySingleton<api::IFingerDetection>::instance(api::g_polySingletonsInfo(), local);
    api::IFingerDetection& b = api::CPolySingleton<api::IFingerDetection>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 5 : 13;
}

const void* volatile biometria_291_sink;

struct SBiometria291Roots {
    SBiometria291Roots()
    {
        biometria_291_sink = reinterpret_cast<const void*>(&DetectaDigital);
    }
} biometria_291_roots;

} // namespace
