#include "app/vota/iexecucaovota.h"

#include "api/util/csystem.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/monitor/cthreadmonitor.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

// (original lines 10-70: content not recovered)
#line 71
// <stubs>
// f3594 · 1923 B · unmatched · name unknown
// ? f3594() { ... }
// </stubs>

void CExecucaoVota::Executa()
{
    CThreadEleitor::GetInst().Start();
    CThreadOperador::GetInst().Start();
    CThreadMonitor::GetInst().Start();
    api::CSystem::Dorme(1000);
    CThreadEleitor::GetInst().Wait();
    CThreadOperador::GetInst().Wait();
    CThreadMonitor::GetInst().Wait();
}

void CExecucaoVota::IniciaThreads()
{
    CThreadEleitor::GetInst().Start();
    CThreadOperador::GetInst().Start();
    CThreadMonitor::GetInst().Start();
    api::CSystem::Dorme(1000);
}

void CExecucaoVota::AguardaThreads()
{
    CThreadEleitor::GetInst().Wait();
    CThreadOperador::GetInst().Wait();
    CThreadMonitor::GetInst().Wait();
}

void CExecucaoVota::IniciaThreadOperador()
{
    CThreadOperador::GetInst().Start();
}

void CExecucaoVota::ParaThreadsOperadorMonitor()
{
    CThreadOperador::GetInst().Stop();
    CThreadMonitor::GetInst().Stop();
}

bool CExecucaoVota::ProcessaEntradaEleitor()
{
    return false;
}

api::CPriorityMessageQueue<api::SMessage>& CExecucaoVota::GetFilaEleitor()
{
    return CThreadEleitor::GetInst().GetMensagens();
}

} // namespace vota
