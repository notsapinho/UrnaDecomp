// Reconstruction's note, not TSE's text. No record names this file: its path is chosen (src/units/158-uenux2-api.mk).
// It holds api::Logger::log (target fn 10815), the key function of api::Logger, whose vtable lies in the data of the
// object that holds api::CRHVoiceTextToSpeech's. CRHVoiceTextToSpeech's own members are not written here yet.
#include "api/audio/crhvoicetexttospeech.h"

#include <iostream>

#include "api/audio/logger.h"

namespace api {

void Logger::log(const std::string& tag, RHVoice_log_level level, const std::string& message) const
{
    if (level == RHVoice_log_level_error) {
        std::clog << "RHVoice [" << tag << "]: " << message << std::endl;
    }
}

} // namespace api
