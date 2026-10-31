#include "app/vota/operador/cthreadoperador.h"

#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/monitor/cthreadmonitor.h"

namespace vota {

CThreadOperador& CThreadOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CThreadOperador());
    }
    return *s_inst;
}

std::unique_ptr<CThreadOperador> CThreadOperador::s_inst;
std::mutex CThreadOperador::s_mutex;

CThreadOperador::CThreadOperador()
    : m_texto1("")
    , m_texto2("")
    , m_texto3(" ")
{
}

CThreadOperador::~CThreadOperador() = default;

void CThreadOperador::ParaOutrasThreads()
{
    CThreadEleitor::GetInst().Stop();
    CThreadMonitor::GetInst().Stop();
}

} // namespace vota
