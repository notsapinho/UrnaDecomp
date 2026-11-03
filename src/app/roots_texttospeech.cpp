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
#include "uenux2/src/api/pattern/cpolysingleton.h"
#include "uenux2/src/api/pattern/cpolysingletonlist.h"

// api::CPolySingleton<api::ITextToSpeech>::set<simulador::CWasmNullTextToSpeech> (target fn 4162, 143 bytes with
// landing pads) is the executable TU's copy too. votaInit (fn 7840, not written) passes it, through invoke_vii's table
// slot 7, the implementer fn 13877 builds (its vptr store is simulador::CWasmNullTextToSpeech's), and through slot 46,
// which holds the same function, the api::CRHVoiceTextToSpeech fn 10842 builds: the two instantiations give one body, a
// reading. fn 8302 (simulador::Inicializa) calls 4162 directly, in the target and in our link, where this object's copy
// links ahead of simulador.cpp.o's. The sink below stands for votaInit's two table slots, so that binaryen keeps 4162
// out of line beside that one call as the target does (measured: with the pointer a namespace-scope variable that
// nothing reads, the link had no set<U> of its own and our 8302 held its body inlined), and goes when votaInit is
// written. What the copy instantiates is this object's too: CPolySingletonList::set<api::ITextToSpeech> (fn 7667, slot
// 65 of 4162's invoke_vii), the two thunks 7667 invokes (fns 14423 and 14456) and has<api::ITextToSpeech> (fn 3281).
//
// 3281 is a thunk of 11 bytes into fn 1166, the body binaryen merges from that TU's has<T> (has<api::ISound>, fn 3343,
// matched from vota_web_wasm.cpp.o, is another thunk of it), where the copy simulador.cpp.o gives at the uenux2 tree's
// flags is a thunk into a body of three constants (pnpm wasm score of 3281 against it: 2 rows inserted). Its target
// callers are fns 2079 (CPolySingleton<api::ITextToSpeech>::instance, cinstrucaovotacaoacessibilidade.cpp's copy) and
// 7667, both in the link, and 14478 (__wasm_call_ctors), not written, for which
// src/units/150-uenux2-eleitor-estados-roots.cpp's TemFala stands.
//
// The order of the sink and the builder below is the executable TU's, which the data of that TU's run gives, not its
// records. The records there are CVotaWebEngine::Init's (1526324, vota_web_wasm.cpp 515:13), push<api::ITextToSpeech>'s
// (1526348, cpolysingletonlist.h 129:19, which fn 7667 loads) and instance<api::ISound>'s (1526584, cpolysingleton.h
// 78:19), and the builder's code (ITextToSpeech's members) has none, so they do not place it. The typeinfos and
// vtables between them do: they lie in the order the TU's code first refers to them, a reading that matches how a
// function's records lie in the order its body is emitted (docs/reference/facts/reading.md §R8). Between 1526324 and
// 1526584 the target has ITextToSpeech's typeinfo (1526340), push's record (1526348), the typeinfo of the error push
// throws and its base's (1526364, 1526376), std::format_error's typeinfo and vtable (1526388, 1526400), the format bool
// strings (1526420, 1526428), CPolySingletonList::debug's s_urna (1526436), the errors' vtables (1526440, 1526460),
// the vtable and typeinfo of the __shared_ptr_pointer that 7667's shared_ptr<api::ITextToSpeech> makes (1526480, table
// slots 290 to 294, and 1526508, whose name is at 463190), and only then ITextToSpeech's vtable (1526520, slots 295 to
// 306). The named ones, in hex, and the words from 1526420 on:
//   /usr/bin/grep -E ' = 0x174(a[3-9a-f]|b[0-3])[0-9a-f];' splat/symbol_addrs.txt
//   python3 -I -c "import struct, sys; sys.path.insert(0, 'tools/extract'); import wasmmod; base, img = wasmmod.Module('target/vota_web_wasm.wasm').memory_image(); print(struct.unpack_from('<28I', img, 1526420 - base))"
// By that reading, push's format code is the first to refer to std::format_error's typeinfo and vtable, and an
// ITextToSpeech constructor's vptr store is what refers to ITextToSpeech's vtable first: four target functions store
// that pointer (i32.const 1526528), the builder (fn 13877) and the destructors 5441, 9427 and 11489, none with a
// record, and which of them the TU reaches first is part of the reading, not a fact; so that TU emitted the set code
// Init reaches, 7667's push in it, and push's format code before what the builder brings. With the sink and its struct
// before urna_texttospeech_constroi, this object emits the 13 .data.rel.ro objects of that run in the target's order
// (only s_urna, a .data object, comes earlier, before format_error's typeinfo):
//   wasm-objdump -x build/out/app/roots_texttospeech.o | /usr/bin/grep -E '^ - segment\[[0-9]+\] <\.data'
// With the builder first (the anonymous namespace moved below it, compiled at this file's rule), it emits
// ITextToSpeech's vtable and std::format_error's typeinfo and vtable ahead of push's record. The root's lines otherwise
// order freely (src/units/README.md "Companion files").
namespace {

void (*volatile urna_texttospeech_set)(simulador::CWasmNullTextToSpeech*, api::TPolySingletonsInfo&);

struct STextToSpeechRoots {
    STextToSpeechRoots()
    {
        urna_texttospeech_set = &api::CPolySingleton<api::ITextToSpeech>::set<simulador::CWasmNullTextToSpeech>;
    }
} urna_texttospeech_roots;

} // namespace

__attribute__((optnone)) std::unique_ptr<api::ITextToSpeech> urna_texttospeech_constroi()
{
    return std::make_unique<simulador::CWasmNullTextToSpeech>();
}
