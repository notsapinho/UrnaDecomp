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
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"
#include "app/vota/eleitor/fimvotacao/cgravaresultado.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

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

void CImprimindoBU::ImprimePrimeiraVia()
{
    if (CSincronizaVota::s_urnaDesligando) {
        return;
    }
    CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_BU, 1);
    ImprimeBU(1, PRINT_WITH_MESSAGE);
    CLogVota::GetInst().LogaMesarioIndagadoQualidadeBU();
    if (CSincronizaVota::s_urnaDesligando) {
        return;
    }
    m_form->Slot2();
}

// (original lines 63-65: content not recovered)
#line 66
void CImprimindoBU::StartState()
{
    comum::md::estadoaplicacao::CEstadoGeralVota& vota = comum::CAppInfo::GetInst().GetVota();

    ASSERT(vota.GetEstadoVota() == EAVIMPRIMIRBU, api::EUA_IMPRIMINDOBU_ESTADOINVALIDO);
    ASSERT(vota.GetQtdBU() == 0, api::EUA_IMPRIMINDOBU_QTDBU_NAO_ZERO);

    ImprimePrimeiraVia();
    m_pNextState = this;
}

void CImprimindoBU::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaMesarioIndicouReimprimirBU();
        ImprimePrimeiraVia();
        m_pNextState = this;
        break;
    case api::INPUT_CONFIRMA: {
        CLogVota::GetInst().LogaMesarioIndicouQualidadeBU();
        comum::md::estadoaplicacao::CEstadoGeralVota& vota = comum::CAppInfo::GetInst().GetVota();
        vota.IncrementaQtdBU();
        if (comum::CAppInfo::EhTreinamentoEleitor()) {
            vota.SetEstadoVota(EAVENCERRADA);
            vota.SetEstadoEncerramento(EAEFIMDOSTRABALHOS);
            CSincronizaVota::SincronizaEstadoGeralVota();
            m_pNextState = &CEmitirMaisBU::GetInst();
        } else {
            vota.SetEstadoVota(EAVGRAVARRESULTADOS);
            CSincronizaVota::SincronizaEstadoGeralVota();
            m_pNextState = &CGravaResultado::GetInst();
        }
        break;
    }
    default:
        break;
    }
}

// (original lines 106-108: content not recovered)
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
