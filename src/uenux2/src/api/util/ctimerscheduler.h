#pragma once

// api::CTimerScheduler: RTTI names the class, a class over api::ITimerScheduler with no data member (fn 5444 allocates
// 4 bytes), and its vtable (@1585396) gives one slot of its own, 10846, before the destructor's shared bodies 174 and 144.
// The path is chosen: no record names a file of this class.

#include "api/util/itimerscheduler.h"

namespace api {

class CTimerScheduler : public ITimerScheduler {
public:
    std::shared_ptr<ITimer> CreateTimer(const std::chrono::milliseconds& interval, std::function<void()> callback) override;
};

} // namespace api
