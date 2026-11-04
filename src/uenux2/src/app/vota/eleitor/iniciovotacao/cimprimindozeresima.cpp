#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"

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
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/cdefinerotaprevotacao.h"
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImprimindoZeresima::CImprimindoZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimindoZeresima& CImprimindoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoZeresima> CImprimindoZeresima::s_inst;
std::mutex CImprimindoZeresima::s_mutex;

void CImprimindoZeresima::StartState()
{
    const std::shared_ptr<api::IForm<api::IScreen>> tela = TelaPorFavorAguarde();
    tela->Slot2();
    CRelVotaUtil::CortaPapel();
    if (CSincronizaVota::s_urnaDesligando) {
        return;
    }
    ImprimeZeresima();
    if (CSincronizaVota::s_urnaDesligando) {
        return;
    }
    ImprimeResumoZeresima();
    if (CSincronizaVota::s_urnaDesligando) {
        return;
    }
    comum::CAppInfo::GetInst().GetVota().SetEstadoVota(comum::EAVZERESIMAIMPRESSA);
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CDefineRotaPreVotacao::GetInst();
}

// (original lines 63-74: content not recovered)
#line 75
void CImprimindoZeresima::ImprimeZeresima()
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

// (original lines 92-101: content not recovered)
#line 102
void CImprimindoZeresima::ImprimeResumoZeresima()
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
