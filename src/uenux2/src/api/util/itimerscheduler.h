#pragma once

// api::ITimerScheduler (/home/rubio/tse/uenux2/src/api/util/itimerscheduler.h, named by the record of CreateInst, line
// 40, column 19; GetInst's record is in itimerscheduler.cpp, line 23, column 12). RTTI names the class, a polymorphic
// class with no base, and its two implementers simulador::CWasmTimerScheduler (vtable @1532172) and
// api::CTimerScheduler (@1585396): slot 0 is the member that makes a timer and slots 1 and 2 the destructor. Slot 0's
// shape is what fn 2024 passes: the result's address, this, a pointer to the 64-bit interval and a pointer to a
// std::function<void ()> it destroys after the call. Its name is chosen. The callback is a reference: fns 2024 and
// 5904 (IInputField's constructor, and BatteryIconDataSource's inlined into comum::CInfoMTLCD's) store the interval's
// temporary before they build the std::function's, and 5904 then reuses the std::function's stack slot, not the
// interval's, for the next temporary. Measured on api/gui/cpowerinformation.cpp's object: by value gives the other
// order and slot; && gives the same object as const&, which is chosen. The implementers' bodies are the
// same either way (fns 10846, 7871: they copy the callback into the timer). CreateInst's throw is the record at line 40; the
// other lines of the class are a choice. CreateInst returns what GetInst returns: fn 5444 tail-calls fn 5443 and its
// result is gone only because no caller reads it (how-to step 2).

#include <chrono>
#include <functional>
#include <memory>

#include "api/pattern/cpolysingleton.h"
#include "api/util/eueutilerror.h"
#include "api/util/itimer.h"

namespace api {

class ITimerScheduler {
public:
    virtual std::shared_ptr<ITimer> CreateTimer(const std::chrono::milliseconds& interval,
                                                const std::function<void()>& callback) = 0;

    virtual ~ITimerScheduler() = default;

    static ITimerScheduler& GetInst();

    template <typename T>
    static ITimerScheduler& CreateInst()
    {
        if (CPolySingletonList::has<ITimerScheduler>()) {
            throw CUeUtilError(EUE_UTIL_TIMERSCHEDULER_RECRIADO, "Tentativa de recriar o singleton");
        }
        CPolySingleton<ITimerScheduler>::set(std::unique_ptr<ITimerScheduler>(new T));
        return GetInst();
    }
};

} // namespace api
