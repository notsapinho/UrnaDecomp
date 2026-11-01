#include "app/vota/eleitor/fimvotacao/ciniciobu.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"
#include "app/vota/eleitor/fimvotacao/cquerimprimirbu.h"

namespace vota {

CInicioBU::CInicioBU()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CInicioBU& CInicioBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInicioBU());
    }
    return *s_inst;
}

std::unique_ptr<CInicioBU> CInicioBU::s_inst;
std::mutex CInicioBU::s_mutex;

void CInicioBU::StartState()
{
    if (comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO &&
        comum::CAppInfo::GetInst().GetVota().GetTreinamentoEleitor()) {
        m_pNextState = &CQuerImprimirBU::GetInst();
    } else {
        m_pNextState = &CImprimindoBU::GetInst();
    }
}

} // namespace vota
