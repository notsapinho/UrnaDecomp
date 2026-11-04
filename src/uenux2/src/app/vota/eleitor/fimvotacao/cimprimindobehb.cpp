#include "app/vota/eleitor/fimvotacao/cimprimindobehb.h"

#include <filesystem>
#include <string>

#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/csigverifier.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/fimvotacao/cretirarmr.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CImprimindoBEHB::CImprimindoBEHB()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimindoBEHB& CImprimindoBEHB::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoBEHB());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoBEHB> CImprimindoBEHB::s_inst;
std::mutex CImprimindoBEHB::s_mutex;

const char TITULO_BEHB[] = "boletim de eleitores\nhabilitados biograficamente";

// (original lines 40-41: content not recovered)
#line 42
void CImprimindoBEHB::StartState()
{
    md::estadoaplicacao::CEstadoGeralVota& vota = CAppInfo::GetInst().GetVota();
    ASSERT(vota.GetEstadoVota() == EAVENCERRADA, api::EUA_IMPRIMINDOBEHB_ESTADOINVALIDO);
    ASSERT(vota.GetEstadoEncerramento() == EAEIMPRIMIROBRIGATORIABU, api::EUA_IMPRIMINDOBEHB_ENCERRINVALIDO);
    ImprimeRelatorio();
    m_pNextState = &CRetirarMR::GetInst();
}

// (original lines 51-52: content not recovered)
#line 53
void CImprimindoBEHB::ImprimeRelatorio()
{
    auto& impresso = api::CPolySingleton<api::IPaperRelatorios>::instance();
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "behb.dat";
    CriaArquivoImprimindo();
    CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_ELEITORES_HABILITADOS_BIOGRAFICAMENTE, 1);
    impresso.PrintFile(arquivo.string(),
                       comum::CSigVerifier(static_cast<comum::ESavdAplic>(1),
                                           comum::CPath::GetPathTrab(comum::FLASH_INTERNA), "behb.dat", "behb.vsu"),
                       TITULO_BEHB, "via única");
    impresso.EndPrintFile();
    RemoveArquivoImprimindo();
}

} // namespace vota
