#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.h"

#include <format>
#include <string>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/cgeradorrelpu.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImpressaoPU::CImpressaoPU()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoPU& CImpressaoPU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoPU());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoPU> CImpressaoPU::s_inst;
std::mutex CImpressaoPU::s_mutex;

void CImpressaoPU::StartState()
{
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    comum::CGeradorRelPU gerador;
    CLogVota::GetInst().loga("Imprimindo parâmetros de urna");
    gerador.Imprime("parâmetros de urna",
                    std::format("{}ª via", appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasPU() + 1));
    appInfo.GetVota().GetNumViasImpressasRelatorios().IncrementaNumViasPU();
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CMaisInformacoes::GetInst();
}

} // namespace vota
