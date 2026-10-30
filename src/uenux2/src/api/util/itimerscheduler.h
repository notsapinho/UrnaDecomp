#pragma once

// api::ITimerScheduler (/home/rubio/tse/uenux2/src/api/util/itimerscheduler.h, named by the record of CreateInst, line
// 40, column 19; GetInst's record is in itimerscheduler.cpp, line 23, column 12). RTTI names the class, a polymorphic
// class with no base, and its two implementers simulador::CWasmTimerScheduler (vtable @1532172) and
// api::CTimerScheduler (@1585396): slot 0 is the member that makes a timer and slots 1 and 2 the destructor. Slot 0's
// shape is what fn 2024 passes: the result's address, this, a pointer to the 64-bit interval and a pointer to a
// std::function<void ()> it destroys after the call. Its name is chosen. This header declares what the input fields
// call and no more: CreateInst is not written, and GetInst (fn 1259) has no body in this tree, as it needs
// api::CPolySingleton.

#include <chrono>
#include <functional>
#include <memory>

#include "api/util/itimer.h"

namespace api {

class ITimerScheduler {
public:
    virtual std::shared_ptr<ITimer> CreateTimer(const std::chrono::milliseconds& interval,
                                                std::function<void()> callback) = 0;

    virtual ~ITimerScheduler() = default;

    static ITimerScheduler& GetInst();
};

} // namespace api
