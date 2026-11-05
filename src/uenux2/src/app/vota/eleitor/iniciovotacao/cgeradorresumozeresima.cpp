// The reconstruction's note: cgeradorresumozeresima.h has each function's evidence and choices.
#include "app/vota/eleitor/iniciovotacao/cgeradorresumozeresima.h"
#include <filesystem>

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/reports/cformpart.h"
#include "api/gui/reports/creport.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/justificativa/cjustificador.h"
#include "app/comum/relatorios/cdatasourcesrelatorio.h"
#include "app/comum/relatorios/cgeradorbu.h"
#include "app/comum/relatorios/cpartecargos.h"
#include "app/comum/relatorios/cparterdv.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"
#include "app/vota/log/clogvota.h"

namespace vota {

// (original lines 30-36: content not recovered)
#line 37
namespace {

api::SharedPaperForm CriaTituloExtratoRDV()
{
    api::CPaperFormBuilder builder;
    const std::size_t qtdJustificativas = comum::CJustificador::GetInst().QuantidadeJustificados();
    ASSERT(qtdJustificativas == 0, api::EUA_GERADORRESUMOZERESIMA_EXTRATORDV_COM_JUSTIFICADOS);
    const comum::CRdv::TVotosCargo votos = comum::CRdvVota::GetInst().GetVotos();

    for (const auto& [cargo, votosCargos] : votos) {
        ASSERT(votosCargos.Total() == 0, api::EUA_GERADORRESUMOZERESIMA_EXTRATORDV_CARGOS_COM_VOTOS);
    }
    ImprimeAvisoSemVotos(builder);
    ImprimeTituloExtratoRDV(builder);
    return builder.Build();
}

} // namespace

std::shared_ptr<api::IForm<api::IPaper>> CriaCabecalhoDetalheZE()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(comum::CCargoDSLabelRelatorio::HeaderDetalheZE, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

std::shared_ptr<api::IForm<api::IPaper>> CriaDetalheCandidato(bool comVotos)
{
    using DataSources = comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>;
    api::CPaperFormBuilder builder;
    builder.AddTextField(comVotos ? DataSources::DetalheCandidato : DataSources::DetalheCandidatoZE,
                         api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

namespace {

using DataSources = comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>;

api::SharedPaperForm CriaTrailerProporcional()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(DataSources::TrailerProporcional, api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    return builder.Build();
}

api::SharedPaperForm CriaTrailerMajoritario()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(DataSources::TrailerMajoritario, api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    return builder.Build();
}

} // namespace

std::vector<std::shared_ptr<api::IReportPart>> CriaPartesExtratoRDV(const std::string& separador)
{
    return {std::make_shared<api::CFormPart>(CriaTituloExtratoRDV()),
            std::make_shared<comum::CParteCargos>(
                std::make_shared<api::CFormPart>(comum::CRelUtil::FormCabecalhoEleicao()),
                std::make_shared<comum::CParteRdv>(
                    std::make_shared<api::CFormPart>(comum::CriaTituloCargo(separador)),
                    std::make_shared<api::CFormPart>(CriaTrailerMajoritario()),
                    std::make_shared<api::CFormPart>(CriaTrailerProporcional()),
                    std::make_shared<api::CFormPart>(CriaTrailerMajoritario()),
                    std::make_shared<api::CFormPart>(api::CPaperFormBuilder().Build())))};
}

api::CReport CriaRelatorioResumoZeresima(const std::string& separador,
                                         const comum::md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    const std::vector<std::shared_ptr<api::IReportPart>> partesRDV = CriaPartesExtratoRDV(separador);
    std::vector<std::shared_ptr<api::IReportPart>> partes = {
        std::make_shared<api::CFormPart>(CRelVotaUtil::CriaCabecalho("Resumo da Zerésima")),
        std::make_shared<api::CFormPart>(comum::CRelUtil::FormRodapeZeresima(
            separador, comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetRodapeZEVOTA(), correspondencia))};
    partes.insert(partes.begin() + 1, partesRDV.begin(), partesRDV.end());
    return api::CReport(partes);
}

void GeraResumoZeresima()
{
    const std::string separador =
        comum::CRelUtil::GetSeparadorFase(comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase());
    const api::CReport relatorio =
        CriaRelatorioResumoZeresima(separador, comum::CAppInfo::GetInst().GetGeral().GetCorrespondencia());
    CLogVota::GetInst().LogaGerandoRelatorio(comum::RELATORIO_RESUMO_ZERESIMA, false);
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "rze.dat";
    api::GeraArquivoRelatorio(arquivo.string(), relatorio);
    CSincronizaVota::SincronizaRelatorios("rze.dat");
    const uedword urnaId = comum::CAppInfo::GetInst().GetGeral().GetCorrespondencia().GetNumeroInternoUrna();
    comum::CAppInfo::GetInst().GetVota().SetUrnaIdGerouZeresima(urnaId);
    CSincronizaVota::SincronizaEstadoGeralVota();
    CLogVota::GetInst().LogaGerandoRelatorio(comum::RELATORIO_RESUMO_ZERESIMA, true);
}

} // namespace vota
