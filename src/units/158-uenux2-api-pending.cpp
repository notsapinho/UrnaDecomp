// Pending members of unit 158, each a trap until it is reconstructed (src/units/README.md "Pending members"):
// - api::CRHVoiceTextToSpeech::DoSynthesize (target fn 10841, slot 11 of the vtable @1585548, 75,081 B), the class's key
//   function, so this object emits the vtable and with it the implicit destructors (fns 5441 and 10838), the compiler's
//   code for the class definition. Not reconstructed: 75,081 B, over RHVoice, libc++ and api callees.
//   It moves into api/audio/crhvoicetexttospeech.cpp with its body. Its stub was in
//   src/uenux2/src/api/audio/alsa/cwavfile.cpp, lines 44 to 47, over the record of api::CWavFile's constructor (47:19),
//   which 10841 inlines; a pending member has no stub (src/units/README.md "Pending members"), and those lines are blank.
// - api::CRHVoiceTextToSpeech's constructor (target fn 10842, 23,822 B: RHVoice's engine set-up, no record), which
//   votaInit (fn 7840, unit 170's TU) invokes through table slot 45 on a new 112-byte object and a path built from "/".
//   It holds that call's place: votaInit's call needs a definition our link has. It is not written; it moves into
//   api/audio/crhvoicetexttospeech.cpp with its body (src/units/440-uenux2-votainit.mk has the reading of the call).
#include "api/audio/crhvoicetexttospeech.h"

namespace api {

std::shared_ptr<CWavFile> CRHVoiceTextToSpeech::DoSynthesize(const std::string&, const SOptions&)
{
    __builtin_trap();
}

CRHVoiceTextToSpeech::CRHVoiceTextToSpeech(const std::filesystem::path&)
{
    __builtin_trap();
}

} // namespace api
