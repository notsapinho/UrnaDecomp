// comum::CGeradorRelVersaoPacoteDados's members, and ImprimeCodigosProcessoEleitoral, which slot 3 holds inlined by
// binaryen. The reconstruction's own note: no record names this file or its lines; cgeradorrelversaopacotedados.h,
// src/units/287-uenux2-cgeradorrelversaopacotedados.mk and src/units/317-uenux2-relatorios-aptos.mk say what is
// evidence and what is chosen.
#include "app/comum/relatorios/cgeradorrelversaopacotedados.h"

#include <format>
#include <functional>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/cpe.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "app/comum/relatorios/adicionaparametro.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/celeitoresaptos.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "app/comum/relatorios/crelutil.h"

namespace comum {

CGeradorRelVersaoPacoteDados::CGeradorRelVersaoPacoteDados(const std::vector<md::CCabecalhoPacote>& pacotes)
    : m_pacotes(pacotes)
{
}

CGeradorRelVersaoPacoteDados::~CGeradorRelVersaoPacoteDados()
{
}

void CGeradorRelVersaoPacoteDados::ImprimeRodape()
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

void CGeradorRelVersaoPacoteDados::Imprime(const std::string& titulo, const std::string& subtitulo)
{
    ImprimeTituloJE();
    ImprimeVersoesPacotes();
    ImprimeRodape();
    m_builder.Show(titulo, subtitulo, true);
}

void ImprimeCodigosProcessoEleitoral(api::CPaperFormBuilder& builder);

void CGeradorRelVersaoPacoteDados::ImprimeTituloJE()
{
    const CLocal& local = CLocal::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const api::CDateTime agora = api::CDateTime::Now();
    const bool contingencia = geral.GetDadoCarga().GetTipoUrna() == eUrnaContingencia;
    CRelUtil::IncluiCabecalhoEleicoesMZS(m_builder, "Versões de Pacotes", local.GetMunicipio(), local.GetZonaID(),
                                         local.GetSecaoID(), local.GetNomeMunicipio(),
                                         contingencia ? CRelUtil::eCabecalhoContingencia : CRelUtil::eCabecalhoSecao,
                                         true);
    if (!contingencia) {
        m_builder.AddTextField(CEleitoresAptos([]() { return CEleitores::GetInst().QuantidadeAptos(); }).Formata(),
                               static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    } else {
        m_builder.AddNewLine(1);
    }
    m_builder.AddNewLine(1);
    m_builder.AddTextField(GetIdentificacaoUrna(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    CRelUtil::ImprimeDataHora(m_builder, agora, "Data", "Hora");
    m_builder.AddNewLine(1);
    ImprimeCodigosProcessoEleitoral(m_builder);
    m_builder.AddNewLine(1);
    CRelUtil::ImprimeResumoCorrespondencia(m_builder, geral.GetCorrespondencia());
    m_builder.AddNewLine(1);
    CRelUtil::ImprimeSeparadorFase(m_builder, geral.GetDadoCarga().GetFase());
    m_builder.AddNewLine(1);
}

void ImprimeCodigosProcessoEleitoral(api::CPaperFormBuilder& builder)
{
    if (!CPE::Existe()) {
        CPE::CreateInst(CAppInfo::GetInst().LeGeralInterno(), FLASH_INTERNA);
    }
    builder.AddTextField(std::format("{:<32s} {:05}", "Código do processo eleitoral",
                                     CPE::GetInst().GetProcessoEleitoral().GetID()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(std::format("{:<32s} {:05}", "Código do pleito 1",
                                     CPE::GetInst().GetProcessoEleitoral().GetPleito1().GetID()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    if (CPE::GetInst().GetProcessoEleitoral().TemPleito2()) {
        builder.AddTextField(std::format("{:<32s} {:05}", "Código do pleito 2",
                                         CPE::GetInst().GetProcessoEleitoral().GetPleito2().GetID()),
                             static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    }
}

void CGeradorRelVersaoPacoteDados::ImprimeVersoesPacotes()
{
    m_builder.AddNewLine(1);
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    for (const md::CCabecalhoPacote& pacote : m_pacotes) {
        const std::string espacos(38 - (pacote.GetNome().size() + pacote.GetVersao().size()), ' ');
        m_builder.AddTextField(std::format("{}{}{}", pacote.GetNome(), espacos, pacote.GetVersao()),
                               static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    }
    const std::string hash = geral.GetResumoHashVersoesPacotes();
    AdicionaParametro(m_builder, "Dados:", hash);
    m_builder.AddNewLine(1);
}

} // namespace comum
