#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

#include "api/util/itimer.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::ITimer, vtable @1532080) and its nested State, which a
// std::make_shared builds (the typeinfo of std::__shared_ptr_emplace<simulador::CWasmTimer::State>). The layout is
// read from simulador::CWasmTimerScheduler's slot 0 (fn 7871), into which binaryen inlined the constructor: 12 bytes,
// the vptr and the shared_ptr<State> at +4/+8; State is 48 bytes, the running flag at +0, a 64-bit generation at +8,
// the interval as an int at +16 (it is what emscripten_async_call takes, fn 7918) and the std::function at +24. The
// constructor takes the interval and the std::function by value (the caller loads the interval before it copies the
// callback into its frame), and so does State's (its by-value std::function is a temporary of the constructor's
// frame, moved into State's member). The destructors store no vptr, so the class is final. The flag and the
// generation are atomics: the callback Start schedules (fn 7909) reloads the shared_ptr from its argument before each
// of them, which only an atomic load forces (with a plain bool and uint64_t clang keeps it in a local); their stores
// and the increment compile as a plain bool's and uint64_t's would. The member names are chosen: no record, symbol
// or string names them (api/util/itimer.h for the slots). Call, Schedule and Fire are chosen too: fn 7918 and fn 7909,
// the callback, each hold the same 16-byte allocation and emscripten_async_call, so one helper binaryen inlined into
// both is a reading, and Fire's being a private static member of this class, not a file-static function, is a choice.
class CWasmTimer final : public api::ITimer {
public:
    CWasmTimer(std::chrono::milliseconds interval, std::function<void()> callback);
    virtual ~CWasmTimer() override;

    virtual void Start() override;
    virtual void Stop() override;
    virtual bool IsRunning() const override;
    virtual void SetInterval(std::chrono::milliseconds interval) override;

private:
    struct State {
        State(std::chrono::milliseconds interval, std::function<void()> callback);

        std::atomic<bool> running;
        std::atomic<std::uint64_t> generation;
        int interval;
        std::function<void()> callback;
    };

    // what a pending emscripten_async_call carries: the state, and the generation it was scheduled for
    struct Call {
        std::shared_ptr<State> state;
        std::uint64_t generation;
    };

    static void Schedule(const std::shared_ptr<State>& state, std::uint64_t generation);
    static void Fire(void* arg);

    std::shared_ptr<State> m_state;
};

} // namespace simulador
