#include "app/vota/cthreadvota.h"

namespace vota {

uebyte CThreadVota::AddTick(size_t milissegundos)
{
    return m_ticks.AddTick(milissegundos);
}

uebyte CThreadVota::AddTick(const std::chrono::milliseconds& tempo)
{
    return m_ticks.AddTick(tempo.count());
}

uebyte CThreadVota::AddStoppedTick(size_t milissegundos)
{
    return m_ticks.AddStoppedTick(milissegundos);
}

uebyte CThreadVota::AddStoppedTick(const std::chrono::milliseconds& tempo)
{
    return m_ticks.AddStoppedTick(tempo.count());
}

void CThreadVota::StopTick(uebyte id)
{
    m_ticks.StopTick(id);
}

void CThreadVota::StartTick(uebyte id)
{
    m_ticks.StartTick(id);
}

} // namespace vota
