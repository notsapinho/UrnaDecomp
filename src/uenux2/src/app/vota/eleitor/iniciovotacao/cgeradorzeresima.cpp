// The reconstruction's note: cgeradorzeresima.h has the functions' evidence and choices.
#include "app/vota/eleitor/iniciovotacao/cgeradorzeresima.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/reports/cformpart.h"
#include "api/gui/reports/creport.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/cgeradorbu.h"
#include "app/comum/relatorios/cpartecandidatos.h"
#include "app/comum/relatorios/cpartecargos.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/cgeradorresumozeresima.h"
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"
#include "app/vota/log/clogvota.h"

namespace vota {

void GeraZeresima()
{
    const api::CReport relatorio = CriaRelatorioZeresima();
    CLogVota::GetInst().LogaGerandoRelatorio(comum::RELATORIO_ZERESIMA, false);
    const std::filesystem::path arquivo = comum::CPath::GetPathTrab(comum::FLASH_INTERNA) / "ze.dat";
    api::GeraArquivoRelatorio(arquivo.string(), relatorio);
    CSincronizaVota::SincronizaRelatorios("ze.dat");
    CLogVota::GetInst().LogaGerandoRelatorio(comum::RELATORIO_ZERESIMA, true);
}

namespace {

api::SharedPaperForm FormLinhas(const std::size_t linhas)
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(linhas);
    return builder.Build();
}

api::SharedPaperForm FormListaCandidatos()
{
    api::CPaperFormBuilder builder;
    ImprimeTituloListaCandidatos(builder);
    return builder.Build();
}

} // namespace

api::CReport CriaRelatorioZeresima()
{
    const std::string separador =
        comum::CRelUtil::GetSeparadorFase(comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase());
    const comum::md::estadoaplicacao::CEstadoGeral& geral = comum::CAppInfo::GetInst().GetGeral();
    const std::vector<std::shared_ptr<api::IReportPart>> partesRDV = CriaPartesExtratoRDV(separador);
    const api::SharedPaperForm tituloCargo = comum::CriaTituloCargo(separador);
    const api::SharedPaperForm semCandidatos = FormSemCandidatos();
    const auto majoritarios = std::make_shared<comum::CParteCandidatosMajoritarios>(
        CriaCabecalhoDetalheZE(), CriaDetalheCandidato(false), FormLinhas(1));
    const auto proporcionais = std::make_shared<comum::CParteCandidatosProporcionais>(
        FormLinhas(0), comum::CRelUtil::FormTituloPartido(), CriaCabecalhoDetalheZE(),
        std::make_shared<api::CFormPart>(CriaDetalheCandidato(false)), FormLinhas(1), FormLinhas(0),
        FormSemCandidatoRegistrado(), &PartidoComCandidatos);
    const auto consultas = std::make_shared<comum::CParteCandidatosConsultas>(CriaCabecalhoDetalheZE(),
                                                                              FormLinhaResposta(), FormLinhas(1));
    std::vector<std::shared_ptr<api::IReportPart>> partes = {
        std::make_shared<api::CFormPart>(CRelVotaUtil::CriaCabecalho("Zerésima")),
        std::make_shared<api::CFormPart>(FormListaCandidatos()),
        std::make_shared<comum::CParteCargos>(
            std::make_shared<api::CFormPart>(comum::CRelUtil::FormCabecalhoEleicao()),
            std::make_shared<comum::CParteCandidatos>(tituloCargo, semCandidatos, majoritarios, proporcionais,
                                                      consultas)),
        std::make_shared<api::CFormPart>(comum::CRelUtil::FormRodapeZeresima(
            separador, comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetRodapeZEVOTA(),
            geral.GetCorrespondencia()))};
    partes.insert(partes.begin() + 1, partesRDV.begin(), partesRDV.end());
    return api::CReport(partes);
}

} // namespace vota
