// The report of the voters enabled by a poll worker, written to a file (comum::CGeradorRelEleitoresHabBiograf::Gera,
// which target fn 12105 holds inlined; fns 11236 to 11239 are its header's std::function members and fn 11240 the
// column header it passes by table slot). The reconstruction's note, not TSE's text: no record names this file, its
// lines or its functions but MontaCabecalho and the class (RTTI); every other name, the other helpers' internal linkage
// and the functions' order are chosen. cgeradorreleleitoreshabbiograf.h and src/units/372-uenux2-relatorios-gerarelatorios.mk say what is
// evidence and what is chosen.
#include "app/comum/relatorios/cgeradorreleleitoreshabbiograf.h"

#include <algorithm>
#include <format>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/reports/cformpart.h"
#include "api/gui/reports/creport.h"
#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "api/util/csynchronizer.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/celeitoresaptos.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/vota/comum/votadefs.h"

namespace comum {

// The key the voters are grouped by: the section, whether they are on a temporary transfer (2) or not (1), and whether
// the section is the urna's own (only for 1). The widths are 12105's loads (a 16-bit section, a word its tree search
// compares unsigned, a byte); the name, the members' names and types of those widths and the defaulted comparison are
// chosen.
struct SChaveSecao {
    ueword secao;
    uedword tipo;
    bool principal;

    auto operator<=>(const SChaveSecao&) const = default;
};

// The line over a group: external, as fn 12105 holds it behind a frame of its own (a reading: clang inlines an
// internal function with one call). Its name and its being a free function are chosen.
std::string DescricaoSecao(const SChaveSecao& chave)
{
    if (chave.tipo == 2) {
        return "Transferência temporária";
    }
    if (!chave.principal) {
        return std::format("Seção agregada: {:04}", chave.secao);
    }
    return "";
}

namespace {

std::string MontaTitulo(CGeradorRelEleitoresHabBiograf::EGeradorRelatorio tipo)
{
    std::string titulo = "Eleitores com habilitação biográfica";
    if (tipo == CGeradorRelEleitoresHabBiograf::eGeradorRecuperador) {
        return std::format("Sistema Recuperador de Dados\n{}", titulo);
    }
    return titulo;
}

std::shared_ptr<api::IReportPart> MontaCabecalho(CGeradorRelEleitoresHabBiograf::EGeradorRelatorio tipo)
{
    const std::string titulo = MontaTitulo(tipo);
    const CLocal& local = CLocal::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const api::CDateTime agora = api::CDateTime::Now();
    api::CPaperFormBuilder builder;
    CRelUtil::IncluiCabecalhoEleicoesMZS(builder, titulo, local.GetMunicipio(), local.GetZonaID(), local.GetSecaoID(),
                                         local.GetNomeMunicipio(), CRelUtil::eCabecalhoSecao, false);
    builder.AddTextField(CEleitoresAptos([]() { return CEleitores::GetInst().QuantidadeAptos(); }).Formata(),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField(GetIdentificacaoUrna(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    CRelUtil::ImprimeDataHora(builder, agora, "Data da emissão", "Hora da emissão");
    builder.AddNewLine(1);
    CRelUtil::ImprimeResumoCorrespondencia(builder, geral.GetCorrespondencia());
    builder.AddNewLine(1);
    CRelUtil::ImprimeSeparadorFase(builder, geral.GetDadoCarga().GetFase());
    builder.AddNewLine(1);
    return std::make_shared<api::CFormPart>(builder.Build());
}

std::string CabecalhoHabilitados()
{
    const ecourna::app::dados::ETipoIdentificadorEleitor tipo = CConfiguracaoEleicao::GetInst().GetTipoIdentificadorPrincipal();
    std::string identificador;
    switch (tipo) {
    case ecourna::app::dados::TipoIDInscricaoEleitoral:
        identificador = "Título";
        break;
    case ecourna::app::dados::TipoIDCPF:
        identificador = "CPF";
        break;
    case ecourna::app::dados::TipoIDNumeroLivre:
        identificador = "Número livre";
        break;
    default:
        break;
    }
    const std::string sequencial = "Sequencial";
    const size_t tamanho = identificador.size() + sequencial.size();
    const std::string espacos = tamanho > 38 ? "" : std::string(38 - tamanho, ' ');
    return sequencial + espacos + identificador;
}

std::shared_ptr<api::IReportPart> MontaTitulos()
{
    api::CPaperFormBuilder builder;
    if (CEleitores::GetInst().QuantidadeHabilitacaoBiografica() == 0) {
        builder.AddNewLine(1);
        return std::make_shared<api::CFormPart>(builder.Build());
    }
    return std::make_shared<api::CFormPart>(builder.Build());
}

std::shared_ptr<api::IReportPart> MontaEleitores()
{
    api::CPaperFormBuilder builder;
    if (CEleitores::GetInst().QuantidadeHabilitacaoBiografica() == 0) {
        builder.AddTextField("Nenhum eleitor passou por habilitação biográfica", static_cast<api::IPaper::EStyle>(1),
                             api::ALINHAMENTO_ESQUERDA);
        return std::make_shared<api::CFormPart>(builder.Build());
    }
    std::map<SChaveSecao, std::vector<std::pair<uedword, std::string>>> secoes;
    const ueword secaoPrincipal = CLocal::GetInst().GetTodasSecoes().at(0).GetNumero();
    CEleitores& eleitores = CEleitores::GetInst();
    for (eleitores.Reset(); !eleitores.IsFim(); eleitores.Next()) {
        const CEleitorDetalhe& detalhe = eleitores.GetDetalheCorrente();
        const std::optional<md::CEleitorDinamico>& dinamico = detalhe.GetDadosDinamicos();
        if (!dinamico || dinamico->GetEstadoComparecimento() != 3 || dinamico->GetTipoHabilitacao() != 2) {
            continue;
        }
        const md::CEleitorDecorator& eleitor = detalhe.GetEleitor();
        const uedword sequencial = eleitor.GetSequencial();
        const std::string identificador =
            md::FormataIdentificador(eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()));
        const ueword secao = eleitor.GetSecao();
        if (!eleitor.IsTTE()) {
            secoes[{secao, 1, secao == secaoPrincipal}].push_back({sequencial, identificador});
        } else {
            secoes[{secao, 2, false}].push_back({sequencial, identificador});
        }
    }
    for (auto& [chave, lista] : secoes) {
        std::sort(lista.begin(), lista.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
    }
    for (const auto& [chave, lista] : secoes) {
        if (chave.tipo == 2 || !chave.principal) {
            vota::AdicionaSeparador(builder, api::ALINHAMENTO_CENTRO);
            builder.AddTextField(DescricaoSecao(chave), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
            vota::AdicionaSeparador(builder, api::ALINHAMENTO_CENTRO);
        }
        builder.AddTextField(&CabecalhoHabilitados, api::ALINHAMENTO_ESQUERDA);
        builder.AddNewLine(1);
        for (const auto& [sequencial, identificador] : lista) {
            const std::string numero = std::format("{:04}", sequencial);
            const size_t tamanho = identificador.size() + numero.size();
            const std::string espacos = tamanho > 38 ? "" : std::string(38 - tamanho, ' ');
            builder.AddTextField(numero + espacos + identificador, static_cast<api::IPaper::EStyle>(1),
                                 api::ALINHAMENTO_ESQUERDA);
        }
        builder.AddNewLine(1);
    }
    return std::make_shared<api::CFormPart>(builder.Build());
}

std::shared_ptr<api::IReportPart> MontaSeparador()
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(1);
    vota::AdicionaSeparador(builder, api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    return std::make_shared<api::CFormPart>(builder.Build());
}

std::shared_ptr<api::IReportPart> MontaRodape(CGeradorRelEleitoresHabBiograf::EGeradorRelatorio tipo)
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(1);
    ImprimeSeparador(builder);
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    builder.AddTextField("Código de identificação da carga", static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddTextField(FormataCodigoCarga(geral.GetCorrespondencia()), static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    ImprimeSeparador(builder);
    builder.AddTextField("Ver: " + api::CStringUtils::GetVersionNumber("10.23.0.1 - DESENVOLVIMENTO"),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField("ASSINATURAS:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    if (tipo == CGeradorRelEleitoresHabBiograf::eGeradorUrna) {
        builder.AddTextField("PRESIDENTE:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
        builder.AddNewLine(2);
        builder.AddTextField("MESÁRIOS:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    } else {
        builder.AddTextField("JUIZ ELEITORAL:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
        builder.AddNewLine(2);
        builder.AddTextField("MINISTÉRIO PÚBLICO:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
        builder.AddNewLine(2);
        builder.AddTextField("TURMA APURADORA:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    }
    builder.AddNewLine(3);
    builder.AddTextField("FISCAIS:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(20);
    builder.AddCut();
    return std::make_shared<api::CFormPart>(builder.Build());
}

} // namespace

CGeradorRelEleitoresHabBiograf::CGeradorRelEleitoresHabBiograf()
    : m_tipo(eGeradorUrna)
{
}

void CGeradorRelEleitoresHabBiograf::Gera(const std::filesystem::path& arquivo) const
{
    const api::CReport relatorio(
        {MontaCabecalho(m_tipo), MontaTitulos(), MontaEleitores(), MontaSeparador(), MontaRodape(m_tipo)});
    api::GeraArquivoRelatorio(arquivo.string(), relatorio);
    api::CSynchronizer::GetInst().Sync();
}

} // namespace comum
