#include "app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CSuspensaoAutomaticaEleitor::~CSuspensaoAutomaticaEleitor() = default;




























































































void CSuspensaoAutomaticaEleitor::FinishState()
{
    CThreadOperador::GetInst().StopTick(m_tick);
    m_bSinalizado = false;
}

} // namespace vota
