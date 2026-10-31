#pragma once

#include <chrono>

#include "api/util/itimer.h"

namespace api {

// RTTI: an si_class of api::ITimer, vtable [5445, 10852, 10850, 10847, 10851, 10848]. api::CTimerScheduler's slot 0 (fn
// 10846) builds it with std::make_shared. Recovered: the head only. Its block's __on_zero_shared (fn 2967) calls through
// the vtable of the object at +16, not +12, so the class is aligned to 8, which one 64-bit member gives; that this member
// is the interval is chosen, as are the constructor's parameter and the path, beside itimer.h.
class CTimer : public ITimer {
public:
    explicit CTimer(std::chrono::milliseconds intervalo);

    void Start() override;
    void Stop() override;
    bool IsRunning() const override;
    void SetInterval(std::chrono::milliseconds interval) override;

private:
    std::chrono::milliseconds m_intervalo;
};

} // namespace api
