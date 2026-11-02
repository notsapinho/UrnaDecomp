// Reconstruction's note, not TSE's text: the file's one record is IExecucaoVota::GetInst's, line 74, column 78, the
// closing parenthesis of POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO's invocation. Every other line, the
// interface's destructor's and CExecucaoVota's members', is chosen (src/units/165-uenux2-app-vota-execucao.mk).
#include "app/vota/iexecucaovota.h"

#include "api/pattern/polysingletongetinst.h"
#include "api/util/csystem.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/monitor/cthreadmonitor.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

// (original lines 14-71: content not recovered)
#line 72
IExecucaoVota::~IExecucaoVota() = default;

POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IExecucaoVota, CExecucaoVota)

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

comum::CAppState* CExecucaoVota::GetEstadoEleitor()
{
    return CThreadEleitor::GetInst().GetEstado();
}

} // namespace vota
