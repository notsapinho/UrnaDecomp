#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"

#include <chrono>

#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {

CEstadoComDesligamentoAutomatico::CEstadoComDesligamentoAutomatico(int eventos)
    : comum::CAppState(eventos | EVENTO_TICK),
      m_limite(-1),
      m_tick(CThreadEleitor::GetInst().AddTick(std::chrono::milliseconds(1000)))
{
}

} // namespace vota
