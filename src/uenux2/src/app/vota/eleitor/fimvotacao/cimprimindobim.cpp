#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"

#include <filesystem>
#include <string>

#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/csigverifier.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobehb.h"
#include "app/vota/eleitor/fimvotacao/cretirarmr.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CImprimindoBim::CImprimindoBim()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimindoBim& CImprimindoBim::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoBim());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoBim> CImprimindoBim::s_inst;
std::mutex CImprimindoBim::s_mutex;

const char TITULO_BIM[] = "boletim de mesários";

// (original lines 44-46: content not recovered)
#line 47
void CImprimindoBim::StartState()
{
    md::estadoaplicacao::CEstadoGeralVota& vota = CAppInfo::GetInst().GetVota();
    ASSERT(vota.GetEstadoVota() == EAVENCERRADA, api::EUA_IMPRIMINDOBIM_ESTADOINVALIDO);
    ASSERT(vota.GetEstadoEncerramento() == EAEIMPRIMIROBRIGATORIABU, api::EUA_IMPRIMINDOBIM_ENCERRINVALIDO);
    ImprimeRelatorio();
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    const CLocal& local = CLocal::GetInst();
    if (!informacao.EhModoDemonstracao() && local.UrnaBiometrica()) {
        m_pNextState = &CImprimindoBEHB::GetInst();
    } else {
        m_pNextState = &CRetirarMR::GetInst();
    }
}

// (original lines 62-63: content not recovered)
#line 64
void CImprimindoBim::ImprimeRelatorio()
{
    auto& impresso = api::CPolySingleton<api::IPaperRelatorios>::instance();
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "bim.dat";
    CriaArquivoImprimindo();
    CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_BIM, 1);
    impresso.PrintFile(arquivo.string(),
                       comum::CSigVerifier(static_cast<comum::ESavdAplic>(1),
                                           comum::CPath::GetPathTrab(comum::FLASH_INTERNA), "bim.dat", "bim.vsu"),
                       TITULO_BIM, "via única");
    impresso.EndPrintFile();
    RemoveArquivoImprimindo();
}

} // namespace vota
