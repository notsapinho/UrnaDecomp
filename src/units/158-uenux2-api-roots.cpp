// Roots of unit 158: the vtables of two classes whose constructors are not reconstructed, kept the way the target keeps
// them. The target reaches each slot below only through its class's vtable, which its builder stores, so the vtable's
// address is the reference the target has (src/units/README.md "Companion files"):
// - api::Logger (@1586188, stored by fn 10842, not reconstructed): slot 2, log (fn 10815), is the key function by
//   choice, in api/audio/crhvoicetexttospeech.cpp;
// - api::CRHVoiceTextToSpeech (@1585548, stored by fn 10842): the vtable is emitted by 158-uenux2-api-pending.o with the
//   implicit destructors (fns 5441, 10838).
// - api::CFixedImage's string constructor (fn 2246): two stand-in callers, below.
// Compiled with UENUX2_CXXFLAGS, as unit 113's roots are (src/units/158-uenux2-api.mk says what PreShow's leaving this
// object changed).
#include <memory>
#include <new>
#include <string>

#include "api/gui/cfixedimage.h"

extern "C" {
extern const char w158_vt_logger[] __asm__("_ZTVN3api6LoggerE");
extern const char w158_vt_rhvoice[] __asm__("_ZTVN3api20CRHVoiceTextToSpeechE");
}

namespace {

// fn 2246, CFixedImage's string constructor, needs no stand-in: its four direct target callers (fns 1263, 3616, 3617
// and 13441) are in the link, 1263 unit 164's CriaIcones, 3616 and 3617 unit 319's, 13441 unit 387's
// vota::ImagemAudioHabilitado (ctelasvota.cpp); the stand-ins for them went.

const void* volatile w158_sink;

struct SW158Roots {
    SW158Roots()
    {
        w158_sink = w158_vt_logger;
        w158_sink = w158_vt_rhvoice;
    }
} w158_roots;

} // namespace
