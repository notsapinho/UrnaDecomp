// Roots of unit 164: api::BatteryIconDataSource<Horizontal> and <Vertical> (src/uenux2/src/api/gui/cpowerinformation.h),
// a class template with no key function whose constructor is not written (the header says what it waits for). In the
// shape src/units/README.md "A class with no key function" gives when the constructor cannot be written (unit 92): an
// optnone function that nothing calls, which wasm-ld drops, calls each instantiation's destructor by its qualified name,
// so this object emits the D2, the D0 and the vtable, since a destructor stores the vptr. The sink keeps the two vtables,
// the reference the target's own code has: their address points are stored by the constructors inlined into fns 502
// (<Horizontal>, 1581580) and 5904 (<Vertical>, 1551916), and by the D2 thunks 5510 and 3837 (the grep of "Companion
// files" for each address lists those four). The D2s and D0s have no other caller here: the target's 5902
// (comum::CInfoMTLCD's destructor), which calls 3837, is not in this tree.
//
// The D2s also store api::IObservable<std::shared_ptr<api::IImage>>'s vptr, as the target's merged D2 body 6049 does, so
// this object emits that class's vtable, D2 and D0 (11651, 11650) as well (src/units/134-uenux2-iobservable.mk).
//
// Compiled with UENUX2_CXXFLAGS, the flags of the uenux2 TUs that emit the class in the target, so no match here rests
// on a flag the tree lacks.
#include "api/gui/cpowerinformation.h"

extern "C" {
extern const char w164_vt_horizontal[] __asm__("_ZTVN3api21BatteryIconDataSourceILNS_17CPowerInformation15IconOrientationE0EEE");
extern const char w164_vt_vertical[] __asm__("_ZTVN3api21BatteryIconDataSourceILNS_17CPowerInformation15IconOrientationE1EEE");
}

using BateriaHorizontal = api::BatteryIconDataSource<api::CPowerInformation::IconOrientation::Horizontal>;
using BateriaVertical = api::BatteryIconDataSource<api::CPowerInformation::IconOrientation::Vertical>;

// not rooted: wasm-ld drops it
__attribute__((optnone, noinline)) void w164_destroi(BateriaHorizontal* horizontal, BateriaVertical* vertical)
{
    horizontal->BateriaHorizontal::~BatteryIconDataSource();
    vertical->BateriaVertical::~BatteryIconDataSource();
}

namespace {

const void* volatile w164_sink;

struct SW164Roots {
    SW164Roots()
    {
        w164_sink = w164_vt_horizontal;
        w164_sink = w164_vt_vertical;
    }
} w164_roots;

} // namespace
