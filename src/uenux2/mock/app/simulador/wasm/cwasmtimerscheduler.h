#pragma once

#include "api/util/itimerscheduler.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::ITimerScheduler, vtable @1532172), the wasm build's timer
// factory. Its object is the vptr alone: fn 8302 allocates 4 bytes and stores it. Slot 0 (fn 7871) builds a CWasmTimer
// with std::make_shared from a copy of the callback (it clones the std::function it was given, where CWasmTimer's
// constructor, inlined there by binaryen, moves its own). The destructors are the shared empty ones (slots 1 and 2:
// 174, 144), left implicit. CreateTimer is out of line, the key function: the class's vtable and typeinfo (1532172,
// 1532192) lie after CWasmTimer's and its State control block's, and before std::__shared_ptr_emplace<CWasmTimer>'s
// (1532204), the make_shared this file instantiates. The member's name is api::ITimerScheduler's (chosen there).
class CWasmTimerScheduler : public api::ITimerScheduler {
public:
    virtual std::shared_ptr<api::ITimer> CreateTimer(const std::chrono::milliseconds& interval,
                                                     std::function<void()> callback) override;
};

} // namespace simulador
