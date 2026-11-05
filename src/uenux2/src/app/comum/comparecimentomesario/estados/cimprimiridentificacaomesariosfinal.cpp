// comum::CImprimirIdentificacaoMesariosFinal
// (/home/rubio/tse/uenux2/src/app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.cpp):
// GetNomeMesario, target fn 5385, whose ASSERT is the record at line 229, column 84, and the members that print the
// report (Imprime and its callees, which fn 12105 holds inlined: cimprimiridentificacaomesariosfinal.h). The lines
// above GetNomeMesario are the original file's, not recovered: the members' lines and order are a choice.

#include "app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.h"

#include <format>
#include <utility>

#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/vota/comum/votadefs.h"

namespace comum {

CImprimirIdentificacaoMesariosFinal::CImprimirIdentificacaoMesariosFinal(bool secao)
    : m_secao(secao),
      m_recuperador(false),
      m_dataHoraEmissao(false)
{
}

std::string CImprimirIdentificacaoMesariosFinal::GetTitulo() const
{
    const std::string titulo = "Boletim de Identificação de Mesários";
    if (m_recuperador) {
        return std::format("Sistema Recuperador de Dados\n{}", titulo);
    }
    return titulo;
}

void CImprimirIdentificacaoMesariosFinal::ImprimeCabecalho()
{
    const CLocal& local = CLocal::GetInst();
    const std::string titulo = GetTitulo();
    CRelUtil::IncluiCabecalhoEleicoesMZS(m_builder, titulo, local.GetMunicipio(), local.GetZonaID(), local.GetSecaoID(),
                                         local.GetNomeMunicipio(),
                                         m_secao ? CRelUtil::eCabecalhoSecao : CRelUtil::eCabecalhoMesaReceptora, false);
}

void CImprimirIdentificacaoMesariosFinal::ImprimeDadosUrna()
{
    CAppInfo& appInfo = CAppInfo::GetInst();
    m_builder.AddTextField(&GetIdentificacaoUrna, api::ALINHAMENTO_ESQUERDA);
    if (CAppInfo::GetInst().TemVota(std::as_const(CAppInfo::GetInst()).GetGeral().GetDadoCarga().GetTurno()) &&
        m_secao) {
        const api::CDateTime inicio = CAppInfo::GetInst().GetVota().GetDtHrInicioAquisicao();
        const api::CDateTime fim = CAppInfo::GetInst().GetVota().GetDtHrFimAquisicao();
        CRelUtil::ImprimeAberturaFechamento(m_builder, inicio, fim);
    }
    if (m_dataHoraEmissao) {
        CRelUtil::ImprimeDataHora(m_builder, api::CDateTime::Now(), "Data da emissão", "Hora da emissão");
        m_builder.AddNewLine(1);
    }
    CRelUtil::ImprimeResumoCorrespondencia(m_builder, appInfo.GetGeral().GetCorrespondencia());
}

void CImprimirIdentificacaoMesariosFinal::ImprimeMesariosAbertura()
{
    if (CRegistradorMesario::GetInst().QuantidadeMesariosInicio() == 0) {
        m_builder.AddTextField("Não houve registro na abertura", static_cast<api::IPaper::EStyle>(1),
                               api::ALINHAMENTO_ESQUERDA);
        return;
    }
    m_builder.AddTextField("Mesários registrados na abertura", static_cast<api::IPaper::EStyle>(1),
                           api::ALINHAMENTO_ESQUERDA);
    m_builder.AddNewLine(1);
    if (!CRegistradorMesario::HasInst()) {
        return;
    }
    for (const auto& [chave, comparecimento] : CRegistradorMesario::GetInst().GetRegistros()) {
        if (comparecimento.GetPeriodoPresente() == 2) {
            continue;
        }
        const md::CEleitorIdentidade mesario = chave.GetMesario();
        m_builder.AddTextField(md::FormataIdentificador(mesario), static_cast<api::IPaper::EStyle>(1),
                               api::ALINHAMENTO_ESQUERDA);
        if (comparecimento.PertenceSecao()) {
            m_builder.AddTextField(GetNomeMesario(mesario.GetIdentificador()), static_cast<api::IPaper::EStyle>(1),
                                   api::ALINHAMENTO_ESQUERDA);
        }
    }
}

void CImprimirIdentificacaoMesariosFinal::ImprimeMesariosFechamento()
{
    const CRegistradorMesario& registrador = CRegistradorMesario::GetInst();
    if (registrador.QuantidadeMesariosFim() == 0) {
        m_builder.AddTextField("Não houve registro no fechamento", static_cast<api::IPaper::EStyle>(1),
                               api::ALINHAMENTO_ESQUERDA);
        return;
    }
    m_builder.AddTextField("Mesários registrados no fechamento", static_cast<api::IPaper::EStyle>(1),
                           api::ALINHAMENTO_ESQUERDA);
    m_builder.AddNewLine(1);
    if (!CRegistradorMesario::HasInst()) {
        return;
    }
    std::size_t separados = 0;
    for (const auto& [chave, comparecimento] : CRegistradorMesario::GetInst().GetRegistros()) {
        if (comparecimento.GetPeriodoPresente() == 1) {
            continue;
        }
        const md::CEleitorIdentidade mesario = chave.GetMesario();
        m_builder.AddTextField(md::FormataIdentificador(mesario), static_cast<api::IPaper::EStyle>(1),
                               api::ALINHAMENTO_ESQUERDA);
        if (comparecimento.PertenceSecao()) {
            m_builder.AddTextField(GetNomeMesario(mesario.GetIdentificador()), static_cast<api::IPaper::EStyle>(1),
                                   api::ALINHAMENTO_ESQUERDA);
        } else {
            m_builder.AddTextField("Nome:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
            m_builder.AddNewLine(1);
            m_builder.AddNewLine(1);
        }
        m_builder.AddTextField("Assinatura:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
        if (separados < registrador.QuantidadeMesariosFim() - 1) {
            m_builder.AddNewLine(1);
            vota::AdicionaSeparador(m_builder, api::ALINHAMENTO_CENTRO);
            ++separados;
        }
    }
}

void CImprimirIdentificacaoMesariosFinal::ImprimeRodape()
{
    m_builder.AddNewLine(1);
    ImprimeSeparador(m_builder);
    CAppInfo& appInfo = CAppInfo::GetInst();
    m_builder.AddTextField("Código de identificação da carga", static_cast<api::IPaper::EStyle>(1),
                           api::ALINHAMENTO_CENTRO);
    m_builder.AddTextField(FormataCodigoCarga(appInfo.GetGeral().GetCorrespondencia()), static_cast<api::IPaper::EStyle>(1),
                           api::ALINHAMENTO_CENTRO);
    m_builder.AddNewLine(1);
    ImprimeSeparador(m_builder);
    m_builder.AddTextField(std::format("Ver: {}", api::CStringUtils::GetVersionNumber("10.23.0.1 - DESENVOLVIMENTO")),
                           static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    m_builder.AddNewLine(1);
    m_builder.AddNewLine(1);
    m_builder.AddCut();
    m_builder.AddNewLine(1);
    m_builder.AddNewLine(1);
}

void CImprimirIdentificacaoMesariosFinal::Imprime(const std::string& arquivo)
{
    GetPrinter().StartReportFile(arquivo);
    ImprimeCabecalho();
    ImprimeDadosUrna();
    ImprimeMesariosAbertura();
    m_builder.AddNewLine(1);
    ImprimeSeparador(m_builder);
    ImprimeMesariosFechamento();
    ImprimeRodape();
    m_builder.Build()->Slot2();
    GetPrinter().EndReportFile();
}

// (original lines 169-224: content not recovered)
#line 225
std::string CImprimirIdentificacaoMesariosFinal::GetNomeMesario(const std::string& titulo)
{
    const CEleitorDetalhe* mesario =
        CEleitores::GetInst().LocalizaEleitor(titulo, ecourna::app::dados::TipoIDInscricaoEleitoral);
    ASSERT(mesario, api::EUA_IMPRIMIRIDENTIFICACAOMESARIOSFINAL_MESARIO_INEXISTENTE);
    const md::CEleitorDecorator& eleitor = mesario->GetEleitor();
    if (!eleitor.GetNomeUrna().empty()) {
        return eleitor.GetNomeUrna().substr(0, 40);
    }
    return eleitor.GetNome().substr(0, 40);
}

} // namespace comum
