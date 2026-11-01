// Roots of unit 164: api::BatteryIconDataSource<Horizontal> and <Vertical> (src/uenux2/src/api/gui/cpowerinformation.h),
// a class template with no key function whose constructors are written in api/gui/cpowerinformation.cpp. The target
// inlines each constructor into its one caller: <Vertical>'s into comum::CInfoMTLCD's constructor (fn 5904, unit 153,
// which that unit's roots call), and <Horizontal>'s into fn 502 (api::CFormBuilder::AddStatusHeader, which builds it
// with std::make_shared), not written. w164_constroi stands for 502 with the one call it has, so that binaryen inlines
// the constructor into it, as into 502. Each constructor stores its class's vtable, which keeps the D2 and D0 (and,
// through the D2s' vptr store, api::IObservable<std::shared_ptr<api::IImage>>'s, 11651 and 11650), and the vtable of
// its lambda's std::function (fns 10979 to 10982 and 10984 for <Horizontal>, 10985 to 10989 for <Vertical>).
// <Vertical>'s D2, D0 and vtable link from cinfomtlcd.cpp.o and <Horizontal>'s from cpowerinformation.cpp.o, both ahead
// of this object.
//
// Compiled with UENUX2_CXXFLAGS, the flags of the uenux2 TUs that emit the class in the target, so no match here rests
// on a flag the tree lacks.
#include <new>

#include "api/gui/cpowerinformation.h"

using BateriaHorizontal = api::BatteryIconDataSource<api::CPowerInformation::IconOrientation::Horizontal>;

namespace {

// stands for fn 502
__attribute__((noinline)) int w164_constroi(void* bateria)
{
    ::new (bateria) BateriaHorizontal();
    return 8;
}

int (*volatile w164_sink)(void*);

struct SW164Roots {
    SW164Roots()
    {
        w164_sink = w164_constroi;
    }
} w164_roots;

} // namespace
