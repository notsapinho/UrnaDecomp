#pragma once

#include <chrono>

namespace api {

// Recovered: RTTI names api::ITimer (typeinfo 1532124), a polymorphic class with no base, and its two implementers
// simulador::CWasmTimer and api::CTimer (vtables @1532080 and @1585352). The target has its typeinfo and no vtable of
// its own: every member is inline or pure. Its six slots are the destructor's two and four members whose wasm types
// and bodies both implementers give: slot 2 stops the timer (CTimer calls slot 3 through the vtable, CWasmTimer has it
// inlined) and starts it again, slot 3 stops it, slot 4 returns the running flag, slot 5 takes a 64-bit interval. The
// interval is a std::chrono::milliseconds: the timers are created with one (the records of the CTextFieldUpdate and
// CImageFieldUpdate constructors spell `const std::chrono::milliseconds &`, and fn 3658 passes it to slot 0 of
// api::ITimerScheduler). No record, symbol or string names the four members or this file, so the names Start, Stop,
// IsRunning and SetInterval, IsRunning's const and the path (beside the recorded api/util/itimerscheduler.h, whose
// ITimerScheduler creates the timers) are chosen.
class ITimer {
public:
    virtual ~ITimer() = default;

    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsRunning() const = 0;
    virtual void SetInterval(std::chrono::milliseconds interval) = 0;
};

} // namespace api
