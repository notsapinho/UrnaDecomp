#include "app/vota/operador/outrasopcoes/citensmenuvota.h"

#include "app/comum/appinfo/cappinfo.h"
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

} // namespace vota
