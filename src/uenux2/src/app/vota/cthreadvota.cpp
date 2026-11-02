#include "app/vota/cthreadvota.h"

#include "app/comum/cappstate.h"

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

comum::CAppState* CThreadVota::GetEstado() const
{
    return m_contexto ? m_contexto->GetState() : nullptr;
}

void CThreadVota::IniciaContexto(comum::CAppState* estado)
{
    m_contexto.reset(new comum::CAppStateContext(estado));
    if (comum::CAppState* atual = m_contexto->GetState()) {
        atual->StartState();
    }
}

} // namespace vota
