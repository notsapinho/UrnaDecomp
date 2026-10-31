#include "cwasmtimerscheduler.h"

#include "cwasmtimer.h"

namespace simulador {

std::shared_ptr<api::ITimer> CWasmTimerScheduler::CreateTimer(const std::chrono::milliseconds& interval,
                                                              std::function<void()> callback)
{
    return std::make_shared<CWasmTimer>(interval, callback);
}

} // namespace simulador
