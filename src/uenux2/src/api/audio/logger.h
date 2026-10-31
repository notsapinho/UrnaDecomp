#pragma once

#include <string>

#include "core/event_logger.hpp"

namespace api {

// RTTI: an si_class of RHVoice::event_logger, vtable [174, 144, 10815]. Recovered: the head only: fn 10842 builds it with
// std::make_shared, and the block's __on_zero_shared goes through the vtable (fn 411), so it is not final. Slot 2 is
// RHVoice's virtual log, overridden by fn 10815, which is not reconstructed. The path is chosen, beside itexttospeech.h,
// the interface of what fn 10842 builds: no record names it.
class Logger : public RHVoice::event_logger {
public:
    void log(const std::string& tag, RHVoice_log_level level, const std::string& message) const override;
};

} // namespace api
