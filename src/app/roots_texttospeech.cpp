// The executable TU's copies of api::ITextToSpeech's inline members (api/audio/itexttospeech.h): Synthesize (target fn
// 11530) with what it calls, the recent-audio cache and the kept map (5758, 5754, 5750, 11436, 11447 and the libc++
// instances they bring), the destructors (11489, 3764, 3746) and SetVoice (11518). src/units/237-uenux2-itexttospeech.mk
// has the evidence, the matches and the measurements.
// - Whose copy. The class has no key function, and its typeinfo and vtable lie in vota_web_wasm.cpp's data
//   (docs/reference/facts/levels.md V1); 11530, 5750, 5758 and 11436 have landing pads, so an -fexceptions object's,
//   which no object of uenux2's rule is (UENUX2_CXXFLAGS has no -fexceptions). So this file compiles at
//   VOTA_WEB_CXXFLAGS, the executable TU's rule, ahead of the uenux2 objects that emit the same members at their tree's
//   flags (cwasmnulltexttospeech.cpp and src/units/158-uenux2-api-pending.cpp; crhvoicetexttospeech.cpp and
//   simulador.cpp emit none of them). That the copies are that TU's is a reading: votaInit (fn 7840, not written)
//   builds the implementer (fn 13877, its table slot in 7840's invoke_ii).
// - The shape (src/units/README.md "Companion files", "A class with no key function"): an optnone function at namespace
//   scope that nothing calls builds the implementer as votaInit does, with std::make_unique; clang emits
//   ITextToSpeech's vtable and every inline member it names here, and wasm-ld drops the builder and keeps those copies,
//   which the implementers' vtables reach. Of what it defines, vota_web_wasm.cpp.o (first on the line) defines 323
//   symbols, whose copies stay that object's; of the other objects of APP_OBJS only roots_boost.o defines one more,
//   std::piecewise_construct, an empty object (llvm-nm --defined-only of each). So its place after roots_coderenv.o
//   picks no function's copy and is a choice. Ahead of the ASN.1 runtime it also takes basic_string::operator=(const&)
//   (fn 1700), whose copy was asn1/AVNDecoder.o's, the runtime's -Os object: the same code, as 1700's match, from this
//   object now, shows.
#include <memory>

#include "uenux2/mock/app/simulador/wasm/cwasmnulltexttospeech.h"

__attribute__((optnone)) std::unique_ptr<api::ITextToSpeech> urna_texttospeech_constroi()
{
    return std::make_unique<simulador::CWasmNullTextToSpeech>();
}
