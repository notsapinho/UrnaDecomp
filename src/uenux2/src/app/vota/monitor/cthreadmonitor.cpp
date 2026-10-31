#include "app/vota/monitor/cthreadmonitor.h"

#include "api/hwil/ipower.h"
#include "api/util/isystemdatetime.h"
#include "app/comum/util/cmonitoraalimentacao.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CThreadMonitor& CThreadMonitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CThreadMonitor());
    }
    return *s_inst;
}

std::unique_ptr<CThreadMonitor> CThreadMonitor::s_inst;
std::mutex CThreadMonitor::s_mutex;

// (original lines 23-50: content not recovered)
#line 51
CThreadMonitor::CThreadMonitor()
    : m_fonePlugado(!api::CPolySingleton<api::IPower>::instance().FoneDesconectado())
    , m_ultimoLog(api::ISystemDateTime::GetInst().GetTime())
{
    comum::util::CMonitoraAlimentacao::CreateInst(static_cast<comum::util::ELogAplicativos>(1));
}

CThreadMonitor::~CThreadMonitor() = default;

void CThreadMonitor::ParaOutrasThreads()
{
    CThreadOperador::GetInst().Stop();
    CThreadEleitor::GetInst().Stop();
}

} // namespace vota
