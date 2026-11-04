#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.h"

#include <format>
#include <string>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/cgeradorrellistaeleitores.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImpressaoListaEleitores::CImpressaoListaEleitores()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoListaEleitores& CImpressaoListaEleitores::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoListaEleitores());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoListaEleitores> CImpressaoListaEleitores::s_inst;
std::mutex CImpressaoListaEleitores::s_mutex;

void CImpressaoListaEleitores::StartState()
{
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    CLogVota::GetInst().loga("Imprimindo lista de eleitores");
    comum::ImprimeListaEleitores(
        "lista de eleitores",
        std::format("{}ª via", appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasEleitores() + 1));
    appInfo.GetVota().GetNumViasImpressasRelatorios().IncrementaNumViasEleitores();
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CMaisInformacoes::GetInst();
}

} // namespace vota
