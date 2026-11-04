#include "app/vota/eleitor/fimvotacao/cimprimirbjust.h"

#include <filesystem>
#include <string>

#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/csigverifier.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"
#include "app/vota/eleitor/fimvotacao/cretirarmr.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CImprimirBJust::CImprimirBJust()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimirBJust& CImprimirBJust::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimirBJust());
    }
    return *s_inst;
}

std::unique_ptr<CImprimirBJust> CImprimirBJust::s_inst;
std::mutex CImprimirBJust::s_mutex;

const char TITULO_BJUST[] = "boletim de justificativa eleitoral";

// (original lines 43-47: content not recovered)
#line 48
void CImprimirBJust::StartState()
{
    md::estadoaplicacao::CEstadoGeralVota& vota = CAppInfo::GetInst().GetVota();
    ASSERT(vota.GetEstadoVota() == EAVENCERRADA, api::EUA_IMPRIMIRBJUST_ESTADOINVALIDO);
    ASSERT(vota.GetEstadoEncerramento() == EAEIMPRIMIROBRIGATORIABU, api::EUA_IMPRIMIRBJUST_ENCERRINVALIDO);
    CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_BUJ, 1);
    imprimeBJust();
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (!informacao.ImprimeBJust()) {
        m_pNextState = &CRetirarMR::GetInst();
    } else {
        m_pNextState = &CImprimindoBim::GetInst();
    }
}

// (original lines 63-66: content not recovered)
#line 67
void CImprimirBJust::imprimeBJust()
{
    auto& impressoraBJust = api::CPolySingleton<api::IPaperRelatorios>::instance();
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "buj.dat";
    CriaArquivoImprimindo();
    impressoraBJust.PrintFile(arquivo.string(),
                              comum::CSigVerifier(static_cast<comum::ESavdAplic>(1),
                                                  comum::CPath::GetPathTrab(comum::FLASH_INTERNA), "buj.dat", "buj.vsu"),
                              TITULO_BJUST, "via única");
    impressoraBJust.EndPrintFile();
    RemoveArquivoImprimindo();
}

} // namespace vota
