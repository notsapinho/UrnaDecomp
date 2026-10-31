// Roots: emit api::IObservable<std::shared_ptr<api::IImage>> (api/pattern/iobservable.h; vtable @1551944, its destructors
// 11651 and 11650), whose virtual members are all inline. A class with no key function has its vtable, D2 and D0 only
// where a TU uses it (docs/reference/facts/reading.md R6). In the target only binaryen's shared destructor body of
// api::BatteryIconDataSource<Horizontal> and <Vertical> (fn 6049, over the thunks 3837 and 5510) stores its vptr, and
// BatteryIconDataSource's constructor is not written, so the builder below makes one and the static constructor keeps the
// vtable in the sink, the reference the target's user has (src/units/README.md "Companion files", "A class with no key
// function"). Compiled with UENUX2_CXXFLAGS, the flags of the uenux2 TUs that emit the class in the target, so no match
// here rests on a flag the tree lacks.
#include "api/gui/iimage.h"
#include "api/pattern/iobservable.h"

extern "C" {
extern const char w134_vt_iobservable[] __asm__("_ZTVN3api11IObservableINSt3__210shared_ptrINS_6IImageEEEEE");
}

// not rooted: wasm-ld drops it, with the constructor it calls
__attribute__((optnone, noinline)) void w134_observavel()
{
    api::IObservable<api::SharedIImage> observavel;
}

namespace {

const void* volatile w134_sink;

struct SW134Roots {
    SW134Roots() { w134_sink = w134_vt_iobservable; }
} w134_roots;

} // namespace
