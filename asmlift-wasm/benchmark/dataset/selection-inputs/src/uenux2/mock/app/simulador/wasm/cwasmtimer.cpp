#include "cwasmtimer.h"

#include <utility>

namespace simulador {

CWasmTimer::State::State(std::chrono::milliseconds interval, std::function<void()> callback)
    : running(false), generation(0), interval(interval.count()), callback(std::move(callback))
{
}

CWasmTimer::CWasmTimer(std::chrono::milliseconds interval, std::function<void()> callback)
    : m_state(std::make_shared<State>(interval, std::move(callback)))
{
}

CWasmTimer::~CWasmTimer()
{
    Stop();
}

void CWasmTimer::Stop()
{
    m_state->running = false;
    ++m_state->generation;
}

bool CWasmTimer::IsRunning() const
{
    return m_state->running;
}

void CWasmTimer::SetInterval(std::chrono::milliseconds interval)
{
    m_state->interval = interval.count();
}

} // namespace simulador
