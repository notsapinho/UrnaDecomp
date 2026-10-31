// Pending: api::CTimerScheduler's slot 0 (fn 10846). It is std::make_shared<api::CTimer> of the interval and the callback:
// a block of 160 bytes (vptr 1585436), a CTimer at +16 (vptr 1585360) that keeps the interval at +8 and the
// std::function at +16, then 100 zero bytes. api::CTimer has no header in this tree, and every member of its vtable waits
// with it. The object's vtable needs the slot, so the member traps here.
#include "api/util/ctimerscheduler.h"

namespace api {

std::shared_ptr<ITimer> CTimerScheduler::CreateTimer(const std::chrono::milliseconds& interval, std::function<void()> callback)
{
    __builtin_trap();
}

} // namespace api
