// comum::CGeradorRelPU, the urna's parameters report. Reconstruction's note: no record names this file or its
// functions; cgeradorrelpu.h says what is chosen, src/units/183-uenux2-relatorios.mk what the bytes decide.
#include "app/comum/relatorios/cgeradorrelpu.h"

#include <format>
#include <string>

#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/cpe.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/crelutil.h"
#include "ecourna/api/security/conversaodatahora.hpp"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/asn/datahoraasn.hpp"
#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipio.hpp"

using ecourna::api::util::CStringUtils;

namespace comum {

void CGeradorRelPU::AdicionaParametro(const std::string& nome, const std::string& valor)
{
    std::string linha = nome;
    linha += CStringUtils::PreencheAEsquerda(valor, ' ', 38 - nome.size());
    m_builder.AddTextField(linha, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

void CGeradorRelPU::ImprimeTituloJE()
{
    const CLocal& local = CLocal::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const api::CDateTime agora = api::CDateTime::Now();
    const bool contingencia = geral.GetDadoCarga().GetTipoUrna() == eUrnaContingencia;
    CRelUtil::IncluiCabecalhoEleicoesMZS(m_builder, "Parâmetros de urna", local.GetMunicipio(), local.GetZonaID(),
                                         local.GetSecaoID(), local.GetNomeMunicipio(),
                                         contingencia ? CRelUtil::eCabecalhoContingencia : CRelUtil::eCabecalhoSecao,
                                         true);
    m_builder.AddNewLine(1);
    m_builder.AddTextField(GetIdentificacaoUrna(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    CRelUtil::ImprimeDataHora(m_builder, agora, "Data", "Hora");
    m_builder.AddNewLine(1);
    CRelUtil::ImprimeResumoCorrespondencia(m_builder, geral.GetCorrespondencia());
    m_builder.AddNewLine(1);
    CRelUtil::ImprimeSeparadorFase(m_builder, geral.GetDadoCarga().GetFase());
    m_builder.AddNewLine(1);
}

void CGeradorRelPU::ImprimeHorarios(const ecourna::app::dados::CConfiguracaoMunicipio& municipio)
{
    const boost::posix_time::ptime emissaoZeresima = municipio.GetHorariosUrna().GetEmissaoZeresima();
    const boost::posix_time::ptime inicioVotacao = municipio.GetHorariosUrna().GetInicioVotacao();
    const boost::posix_time::ptime encerramentoVotacao = municipio.GetHorariosUrna().GetEncerramentoVotacao();
    const boost::posix_time::ptime terminoVotacao = municipio.GetHorariosUrna().GetTerminoVotacao();
    AdicionaParametro("Emissão de zerésima",
                      std::format("{} -", ecourna::app::dados::asn::FormataHora(emissaoZeresima)));
    AdicionaParametro("", ecourna::api::security::FormataData(emissaoZeresima));
    AdicionaParametro("Início da votação", std::format("{} -", ecourna::app::dados::asn::FormataHora(inicioVotacao)));
    AdicionaParametro("", ecourna::api::security::FormataData(inicioVotacao));
    AdicionaParametro("Encerramento da votação",
                      std::format("{} -", ecourna::app::dados::asn::FormataHora(encerramentoVotacao)));
    AdicionaParametro("", ecourna::api::security::FormataData(encerramentoVotacao));
    AdicionaParametro("Término compulsório", std::format("{} -", ecourna::app::dados::asn::FormataHora(terminoVotacao)));
    AdicionaParametro("", ecourna::api::security::FormataData(terminoVotacao));
}

void CGeradorRelPU::ImprimeParametros()
{
    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    const ecourna::app::dados::CConfiguracaoMunicipio& municipio =
        CConfiguracaoEleicao::GetInst().GetConfiguracaoMunicipio();
    const md::estadoaplicacao::CEstadoGeral geral = CAppInfo::GetInst().LeGeralInterno();
    md::CPleito pleito = CConfiguracaoEleicao::GetInst().GetPleito();
    if (geral.GetDadoCarga().GetTipoUrna() == eUrnaContingencia) {
        if (!CPE::Existe()) {
            CPE::CreateInst(geral, FLASH_INTERNA);
        }
        if (CPE::GetInst().GetProcessoEleitoral().TemPleito2()) {
            const api::CDate hoje;
            const md::CPleito& pleito2 = CPE::GetInst().GetProcessoEleitoral().GetPleito2();
            if (pleito2.GetData() == hoje || pleito2.GetData() < hoje) {
                pleito = pleito2;
            }
        }
    }
    ImprimeHorarios(municipio);
    const ecourna::app::dados::CParametrosUrna& parametros = configuracao.GetParametrosUrna();
    AdicionaParametro("Zerésimas", std::to_string(static_cast<int>(parametros.GetNumZeresimas())));
    AdicionaParametro("BUs do Vota obrigatórios", std::to_string(static_cast<int>(parametros.GetNumBUVotaObrigatorios())));
    AdicionaParametro("BUs do Vota adicionais", std::to_string(static_cast<int>(parametros.GetNumBUVotaAdicionais())));
    AdicionaParametro("BUs do RED obrigatórios", std::to_string(static_cast<int>(parametros.GetNumBUFinalREDObrigat())));
    AdicionaParametro("BUs do RED adicionais", std::to_string(static_cast<int>(parametros.GetNumBUFinalREDAdic())));
    AdicionaParametro("BUs do SA obrigatórios", std::to_string(static_cast<int>(parametros.GetNumBUFinalSAObrigat())));
    AdicionaParametro("BUs do SA adicionais", std::to_string(static_cast<int>(parametros.GetNumBUFinalSAAdic())));
    AdicionaParametro("Aceitar justificativa", parametros.GetAceitarJustificativa() ? std::string("Sim") : std::string("Não"));
    AdicionaParametro("Apresentar partido", parametros.GetApresentarPartido() ? std::string("Sim") : std::string("Não"));
    AdicionaParametro("Imprimir QR Code no BU", parametros.GetImprimirQrCodeNoBU() ? std::string("Sim") : std::string("Não"));
    AdicionaParametro("Registrar mesários", parametros.GetRegistrarMesarios() ? std::string("Sim") : std::string("Não"));
    AdicionaParametro("Pedir ano nascimento", parametros.GetPedeAnoNascimentoEleitor() ? std::string("Sim") : std::string("Não"));
    AdicionaParametro("Tempo desligamento auto",
                      std::to_string(static_cast<int>(parametros.GetTempoDesligamentoAutomatico())));
    AdicionaParametro("Tempo aviso desligamento auto",
                      std::to_string(static_cast<int>(parametros.GetTempoAvisoDesligamentoAutomatico())));
}

void CGeradorRelPU::ImprimeRodape()
{
    m_builder.AddNewLine(1);
    ImprimeSeparador(m_builder);
    CAppInfo& appInfo = CAppInfo::GetInst();
    m_builder.AddTextField("Código de identificação da carga", static_cast<api::IPaper::EStyle>(1),
                           api::ALINHAMENTO_CENTRO);
    m_builder.AddTextField(FormataCodigoCarga(appInfo.GetGeral().GetCorrespondencia()),
                           static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    m_builder.AddNewLine(1);
    ImprimeSeparador(m_builder);
    m_builder.AddTextField(std::format("Ver: {}", api::CStringUtils::GetVersionNumber("10.23.0.1 - DESENVOLVIMENTO")),
                           static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    m_builder.AddNewLine(2);
    m_builder.AddCut();
    m_builder.AddNewLine(4);
}

void CGeradorRelPU::Imprime(const std::string& titulo, const std::string& via)
{
    ImprimeTituloJE();
    ImprimeParametros();
    ImprimeRodape();
    m_builder.Show(titulo, via, true);
}

} // namespace comum
