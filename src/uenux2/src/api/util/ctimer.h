#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

#include "api/util/itimer.h"

namespace api {

// RTTI: an si_class of api::ITimer, vtable [5445, 10852, 10850, 10847, 10851, 10848]. api::CTimerScheduler's slot 0 (fn
// 10846) builds it with std::make_shared, its constructor inlined there. The layout is what that constructor stores and
// what the destructor (fn 5445) destroys, in reverse order: the interval at +8 (slot 5 stores it, a 64-bit word), the
// std::function at +16 (fn 10846 moves the callback into it), the running flag at +40 (slots 2 and 3 store 1 and 0, slot
// 4 returns it), then 100 bytes fn 10846 zero-fills: a std::condition_variable at +44 (slot 3 notifies it), a std::mutex
// at +92 (the thread's loop locks it, fn 10849), a std::thread at +116 (slot 3 joins it, the destructor tests it) and a
// std::mutex at +120 (slot 3 holds it while it joins; the destructor then destroys it). The destructor is out of line
// (the deleting one, fn 10852, calls it and then frees this) and inlines Stop. Start (fn 10850) calls Stop
// through the vtable, sets the flag and starts the thread on a lambda of this alone (an 8-byte tuple with the
// __thread_struct); with no threads in the build the std::thread constructor always throws, so the rest of Start is gone,
// and the lambda's loop is in the thread proxy, fn 10849. The members' names, the constructor's parameters, the flag's
// type and the path (beside itimer.h) are chosen.
class CTimer : public ITimer {
public:
    CTimer(std::chrono::milliseconds intervalo, std::function<void()> callback)
        : m_intervalo(intervalo), m_callback(std::move(callback))
    {
    }

    ~CTimer() override;

    void Start() override;
    void Stop() override;
    bool IsRunning() const override;
    void SetInterval(std::chrono::milliseconds interval) override;

private:
    std::chrono::milliseconds m_intervalo;
    std::function<void()> m_callback;
    bool m_rodando = false;
    std::condition_variable m_condicao;
    std::mutex m_mutex;
    std::thread m_thread;
    std::mutex m_mutexThread;
};

} // namespace api
