#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"

#include <filesystem>
#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cpaperformbuilder.h"
#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/csigverifier.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CImprimindoBU::CImprimindoBU()
    : comum::CAppState(EVENTO_ENTRADA),
      m_form(CTelasVota::GetInst().GetTelaImprimindoBU())
{
}

CImprimindoBU::~CImprimindoBU() = default;

CImprimindoBU& CImprimindoBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoBU());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoBU> CImprimindoBU::s_inst;
std::mutex CImprimindoBU::s_mutex;

const char TITULO_BOLETIM[] = "boletim de urna";

// (original lines 43-108: content not recovered)
#line 109
void CImprimindoBU::ImprimeBU(uebyte numVia, PrintMessageMode modo)
{
    auto& impresso = api::CPolySingleton<api::IPaperRelatorios>::instance();
    const comum::md::estadoaplicacao::CEstadoGeralVota& estVota = comum::CAppInfo::GetInst().GetVota();

    ASSERT(estVota.GetQtdBU() == numVia - 1, api::EUA_IMPRIMINDOBU_QTD_BU_VIAS);

    const std::string titulo = std::format("{}a. VIA", numVia);
    api::CPaperFormBuilder builder;
    builder.AddTextField(titulo, static_cast<api::IPaper::EStyle>(2), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(3);
    const std::shared_ptr<api::IForm<api::IPaper>> formulario = builder.Build();
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "bu.dat";
    CriaArquivoImprimindo();
    impresso.PrintFile(arquivo.string(),
                       comum::CSigVerifier(static_cast<comum::ESavdAplic>(1),
                                           comum::CPath::GetPathTrab(comum::FLASH_INTERNA), "bu.dat", "bu.vsu"),
                       formulario,
                       modo == PRINT_WITH_MESSAGE ? TITULO_BOLETIM : "",
                       modo == PRINT_WITH_MESSAGE ? std::format("{}ª via", numVia) : "");
    impresso.EndPrintFile();
    RemoveArquivoImprimindo();
}

} // namespace vota
