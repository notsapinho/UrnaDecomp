// Roots of unit 158: the vtables of three classes whose constructors are not reconstructed, kept the way the target keeps
// them. The target reaches each slot below only through its class's vtable, which its builder stores, so the vtable's
// address is the reference the target has (src/units/README.md "Companion files"):
// - api::CPreShowClearScreen (@1577888, stored by fn 11140, a thunk of binaryen's 6117 with fn 886, not reconstructed):
//   the class has no key function, so w158_preshow, an optnone builder that nothing calls and wasm-ld drops, makes
//   clang emit the vtable and the inline PreShow (fn 11139) here, as "A class with no key function" says;
// - api::Logger (@1586188, stored by fn 10842, not reconstructed): slot 2, log (fn 10815), is the key function, in
//   api/audio/crhvoicetexttospeech.cpp;
// - api::CRHVoiceTextToSpeech (@1585548, stored by fn 10842): the vtable is emitted by 158-uenux2-api-pending.o with the
//   implicit destructors (fns 5441, 10838).
// - api::CFixedImage's string constructor (fn 2246): two stand-in callers, below.
// Compiled with UENUX2_CXXFLAGS, as unit 113's roots are, so that PreShow, the one function of a class this object emits
// to match, is the tree's code.
#include <memory>
#include <new>
#include <string>

#include "api/gui/cfixedimage.h"
#include "api/gui/cpreshowclearscreen.h"

extern "C" {
extern const char w158_vt_preshow[] __asm__("_ZTVN3api19CPreShowClearScreenE");
extern const char w158_vt_logger[] __asm__("_ZTVN3api6LoggerE");
extern const char w158_vt_rhvoice[] __asm__("_ZTVN3api20CRHVoiceTextToSpeechE");
}

__attribute__((optnone, noinline)) api::IPreShow<api::IScreen>* w158_preshow()
{
    return new api::CPreShowClearScreen;
}

namespace {

// fn 2246, CFixedImage's string constructor, has four direct callers in the target (fns 1263, 3616, 3617 and 13441),
// none reconstructed. These two stand in for them, with bodies no target function has.
__attribute__((noinline)) std::shared_ptr<api::IImage> NovaImagemFixa(const std::string& arquivo)
{
    return std::make_shared<api::CFixedImage>(arquivo);
}

__attribute__((noinline)) void ImagemFixaEm(void* destino, const std::string& arquivo)
{
    new (destino) api::CFixedImage(arquivo);
}

const void* volatile w158_sink;

struct SW158Roots {
    SW158Roots()
    {
        w158_sink = w158_vt_preshow;
        w158_sink = w158_vt_logger;
        w158_sink = w158_vt_rhvoice;
        w158_sink = reinterpret_cast<const void*>(&NovaImagemFixa);
        w158_sink = reinterpret_cast<const void*>(&ImagemFixaEm);
    }
} w158_roots;

} // namespace
