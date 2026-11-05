#include "app/vota/operador/outrasopcoes/citensmenuvota.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"

namespace vota {

unsigned int CItemImprimeEstadoUrnaVota::Slot3()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    return appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasEstadoUrna();
}

unsigned int CItemImprimeListaEleitoresVota::Slot3()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    return appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasEleitores();
}

unsigned int CItemVersoesPacotesVota::Slot3()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    return appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasVersoesDados();
}

unsigned int CItemParametrosUrnaVota::Slot3()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    return appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasPU();
}

CItemVisualizarCandidatosVota::~CItemVisualizarCandidatosVota() = default;

bool CItemVisualizarCandidatosVota::Slot2()
{
    const std::map<comum::TCargoID, comum::md::CCargo> cargos = comum::CCargos::GetInst().GetMapaCargos();
    for (const auto& [chave, candidatura] : comum::CCandidaturas::GetInst().GetRegistros()) {
        const auto it = cargos.find(candidatura.GetCargoID());
        if (it != cargos.end() && it->second.HasDetalheCandidato()) {
            return true;
        }
    }
    return false;
}

} // namespace vota
