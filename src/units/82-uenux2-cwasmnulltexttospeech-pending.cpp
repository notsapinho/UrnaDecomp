// Pending members: the api::ITextToSpeech member src/uenux2/src/api/audio/itexttospeech.h does not define yet. It is
// inline in the original (the class has no key function: the header says how the data shows it), and a vtable slot needs
// it defined, so this trap is a key function of our link only and this object emits ITextToSpeech's vtable and typeinfo,
// strong where the original's are weak (src/units/README.md "Pending members"). Its body is NOT the target's, it traps.
// Target function: Synthesize 11530 (vtable slot 0, 415 B). It waits for its three callees, reached through the table
// from the executable's TU, which no unit compiles yet: 5758 (makes the key: std::format("{}:{}:{}:{}:{}", ...), slot
// 207), 5754 (looks the key up in both containers, slot 208) and 5750 (stores a result, slot 209), each unnamed. 11530
// itself holds that TU's code: invoke_* calls with landing pads, and the string copy (fn 243) and destructors (fn 149)
// as calls, which the uenux2 flags inline.
#include "api/audio/itexttospeech.h"

namespace api {

std::shared_ptr<CWavFile> ITextToSpeech::Synthesize(const std::string& text)
{
    __builtin_trap();
}

} // namespace api
