#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.h"

#include <format>
#include <string>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/crelatoriotesteimpressora.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImpressaoEstadoUrna::CImpressaoEstadoUrna()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoEstadoUrna& CImpressaoEstadoUrna::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoEstadoUrna());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoEstadoUrna> CImpressaoEstadoUrna::s_inst;
std::mutex CImpressaoEstadoUrna::s_mutex;

void CImpressaoEstadoUrna::StartState()
{
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const comum::CRelatorioTesteImpressora relatorio;
    CLogVota::GetInst().LogaImprimindoRelatorioEstadoUrna();
    relatorio.Imprime(
        "estado da urna",
        std::format("{}ª via", appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasEstadoUrna() + 1));
    appInfo.GetVota().GetNumViasImpressasRelatorios().IncrementaNumViasEstadoUrna();
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CMaisInformacoes::GetInst();
}

} // namespace vota
