#include "app/vota/cexecucaovotacooperativa.h"

#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {

CExecucaoVotaCooperativa::CExecucaoVotaCooperativa(comum::CAppState* estadoInicial)
    : m_estadoInicial(estadoInicial)
{
}

void CExecucaoVotaCooperativa::Executa()
{
    CThreadEleitor::GetInst().IniciaContexto(m_estadoInicial);
}

void CExecucaoVotaCooperativa::IniciaThreads()
{
    CThreadEleitor::GetInst().IniciaContexto(m_estadoInicial);
}

void CExecucaoVotaCooperativa::AguardaThreads()
{
}

void CExecucaoVotaCooperativa::IniciaThreadOperador()
{
}

void CExecucaoVotaCooperativa::ParaThreadsOperadorMonitor()
{
}

api::CPriorityMessageQueue<api::SMessage>& CExecucaoVotaCooperativa::GetFilaEleitor()
{
    return CThreadEleitor::GetInst().GetMensagens();
}

comum::CAppState* CExecucaoVotaCooperativa::GetEstadoEleitor()
{
    return CThreadEleitor::GetInst().GetEstado();
}

} // namespace vota
