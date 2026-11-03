#include "app/vota/eleitor/iniciovotacao/ciniciozeresima.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.h"
#include "app/vota/eleitor/iniciovotacao/cquerimprimirzeresima.h"

namespace vota {

CInicioZeresima::CInicioZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CInicioZeresima& CInicioZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInicioZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CInicioZeresima> CInicioZeresima::s_inst;
std::mutex CInicioZeresima::s_mutex;

void CInicioZeresima::StartState()
{
    comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVAGUARDAHORAZERESIMA);
    CSincronizaVota::SincronizaEstadoGeralVota();
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        m_pNextState = &CQuerImprimirZeresima::GetInst();
    } else {
        m_pNextState = &CConfirmaImpressaoZeresima::GetInst();
    }
}

} // namespace vota
