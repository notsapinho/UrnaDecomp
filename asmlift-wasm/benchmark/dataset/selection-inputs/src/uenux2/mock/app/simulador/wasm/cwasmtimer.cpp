#include "cwasmtimer.h"

#include <emscripten.h>

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

void CWasmTimer::Start()
{
    Stop();
    m_state->running = true;
    Schedule(m_state, ++m_state->generation);
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

void CWasmTimer::Schedule(const std::shared_ptr<State>& state, std::uint64_t generation)
{
    emscripten_async_call(&CWasmTimer::Fire, new Call{state, generation}, state->interval);
}

void CWasmTimer::Fire(void* arg)
{
    const std::unique_ptr<Call> call(static_cast<Call*>(arg));
    const std::shared_ptr<State>& state = call->state;
    if (state->running && state->generation == call->generation) {
        state->callback();
        if (state->running && state->generation == call->generation)
            Schedule(state, call->generation);
    }
}

} // namespace simulador
