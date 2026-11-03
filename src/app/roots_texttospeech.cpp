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
#include "uenux2/src/api/pattern/cpolysingletonlist.h"

__attribute__((optnone)) std::unique_ptr<api::ITextToSpeech> urna_texttospeech_constroi()
{
    return std::make_unique<simulador::CWasmNullTextToSpeech>();
}

// api::CPolySingletonList::has<api::ITextToSpeech> (target fn 3281) is the executable TU's copy too: its 11 bytes are a
// thunk into fn 1166, the body binaryen merges from that TU's has<T> (has<api::ISound>, fn 3343, matched from
// vota_web_wasm.cpp.o, is another thunk of it), where the copy simulador.cpp.o gives at the uenux2 tree's flags is a
// thunk into a body of three constants (pnpm wasm score of 3281 against it: 2 rows inserted). Its target callers are fn
// 2079 (CPolySingleton<api::ITextToSpeech>::instance, cinstrucaovotacaoacessibilidade.cpp's copy, in the link) and fns
// 7667 (the executable TU's set<api::ITextToSpeech>) and 14478 (__wasm_call_ctors), not written, for which
// src/units/150-uenux2-eleitor-estados-roots.cpp's TemFala stands. The instance goes when 7667 lands, whose object then
// gives the same copy.
template bool api::CPolySingletonList::has<api::ITextToSpeech>(const api::TPolySingletonsInfo&);
