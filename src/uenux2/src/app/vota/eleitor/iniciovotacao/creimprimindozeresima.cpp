#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"

#include <filesystem>
#include <format>
#include <string>

#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/relatorios/csigverifier.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CReimprimindoZeresima::CReimprimindoZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CReimprimindoZeresima& CReimprimindoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReimprimindoZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CReimprimindoZeresima> CReimprimindoZeresima::s_inst;
std::mutex CReimprimindoZeresima::s_mutex;

// (original lines 35-42: content not recovered)
#line 43
void CReimprimindoZeresima::StartState()
{
    ImprimeZeresima();
    m_pNextState = &CReimprimindoResumoZeresima::GetInst();
}

void CReimprimindoZeresima::ImprimeZeresima()
{
    auto& impresso = api::CPolySingleton<api::IPaperRelatorios>::instance();
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "ze.dat";
    const int vias = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumZeresimas();
    for (int via = 0; via < vias; ++via) {
        CriaArquivoImprimindo();
        CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_ZERESIMA, via + 1);
        impresso.PrintFile(arquivo.string(),
                           comum::CSigVerifier(static_cast<comum::ESavdAplic>(1),
                                               comum::CPath::GetPathTrab(comum::FLASH_INTERNA), "ze.dat", "ze.vsu"),
                           "zerésima", std::format("via {} de {}", via + 1, vias));
        RemoveArquivoImprimindo();
    }
    impresso.EndPrintFile();
}

} // namespace vota
