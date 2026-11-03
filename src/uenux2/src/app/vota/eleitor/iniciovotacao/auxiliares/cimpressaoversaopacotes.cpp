#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.h"

#include <filesystem>
#include <format>
#include <string>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/cgeradorrelversaopacotedados.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/ledadosdisponiveiscarga.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImpressaoVersaoPacotes::CImpressaoVersaoPacotes()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoVersaoPacotes& CImpressaoVersaoPacotes::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoVersaoPacotes());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoVersaoPacotes> CImpressaoVersaoPacotes::s_inst;
std::mutex CImpressaoVersaoPacotes::s_mutex;

void CImpressaoVersaoPacotes::StartState()
{
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const comum::md::CDadosDisponiveisCarga dados =
        LeDadosDisponiveisCarga((comum::CPath::GetPathEstatico(comum::FLASH_INTERNA) / "dadoscarga.dat").string());
    comum::CGeradorRelVersaoPacoteDados gerador(dados.GetPacotes());
    CLogVota::GetInst().loga("Imprimindo versões dos pacotes");
    gerador.Imprime("versões dos pacotes",
                    std::format("{}ª via", appInfo.GetVota().GetNumViasImpressasRelatorios().GetNumViasVersoesDados() + 1));
    appInfo.GetVota().GetNumViasImpressasRelatorios().IncrementaNumViasVersoesDados();
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CMaisInformacoes::GetInst();
}

} // namespace vota
