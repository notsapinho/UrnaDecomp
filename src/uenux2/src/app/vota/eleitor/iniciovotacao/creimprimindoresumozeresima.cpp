#include "app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.h"

#include <filesystem>
#include <format>
#include <memory>
#include <string>

#include "api/gui/iform.h"
#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/csigverifier.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/cdefinerotaposreinicio.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CReimprimindoResumoZeresima::CReimprimindoResumoZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CReimprimindoResumoZeresima& CReimprimindoResumoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReimprimindoResumoZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CReimprimindoResumoZeresima> CReimprimindoResumoZeresima::s_inst;
std::mutex CReimprimindoResumoZeresima::s_mutex;

// (original lines 41-47: content not recovered)
#line 48
void CReimprimindoResumoZeresima::StartState()
{
    const std::shared_ptr<api::IForm<api::IScreen>> tela = TelaPorFavorAguarde();
    tela->Slot2();
    ImprimeResumoZeresima();
    comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVZERESIMAIMPRESSA);
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CDefineRotaPosReinicio::GetInst();
}

void CReimprimindoResumoZeresima::ImprimeResumoZeresima()
{
    auto& impresso = api::CPolySingleton<api::IPaperRelatorios>::instance();
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "rze.dat";
    const int vias = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumZeresimas();
    for (int via = 0; via < vias; ++via) {
        CriaArquivoImprimindo();
        CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_RESUMO_ZERESIMA, via + 1);
        impresso.PrintFile(arquivo.string(),
                           comum::CSigVerifier(static_cast<comum::ESavdAplic>(1),
                                               comum::CPath::GetPathTrab(comum::FLASH_INTERNA), "rze.dat", "rze.vsu"),
                           "resumo da zerésima", std::format("via {} de {}", via + 1, vias));
        RemoveArquivoImprimindo();
    }
    impresso.EndPrintFile();
}

} // namespace vota
