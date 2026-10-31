// Pending: api::CTimerScheduler's slot 0 (fn 10846). It is std::make_shared<api::CTimer> of the interval and the callback:
// a block of 160 bytes (vptr 1585436), a CTimer at +16 (vptr 1585360) that keeps the interval at +8 and the
// std::function at +16, then 100 zero bytes. api::CTimer has no header in this tree, and every member of its vtable waits
// with it. The object's vtable needs the slot, so the member traps here.
//
// Pending: api::CAjusteDataHora's slot 0 (fn 10875), SetTime of what fn 1381 reads from an api::CDateTime: a struct tm from
// its date and time, handed to fn 2961. 1381 has no body in this tree, and api/util/cdatetime.cpp is a stub-only file.
// That member is the class's key function here, so this object emits the vtable.
#include "api/util/cajustedatahora.h"
#include "api/util/ctimerscheduler.h"

namespace api {

std::shared_ptr<ITimer> CTimerScheduler::CreateTimer(const std::chrono::milliseconds& interval, std::function<void()> callback)
{
    __builtin_trap();
}

void CAjusteDataHora::Ajusta(const CDateTime& dataHora)
{
    __builtin_trap();
}

} // namespace api
