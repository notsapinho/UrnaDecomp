// comum::CRelUtil (/home/rubio/tse/uenux2/src/app/comum/relatorios/crelutil.cpp). The reconstruction's own note: the blank
// lines stand for text not recovered. The file's five records are all written: TituloPartido's (line 58, column 15,
// target fn 11181), GetIDCargaFormatado's (line 69, column 15, fn 2786), IncluiCabecalhoEleicoesMZS's (line 307, column
// 19, fn 1543), DSCodigoVerificador's (line 412, column 27, fn 11182) and GetSeparadorFase's (line 554, column 23, fn
// 1919). Each function's first line is chosen so that its throw, or its CPolySingleton<CCalculaCV>::instance() call,
// lands on its record's line. TituloPartido is in the anonymous namespace, as its record names it. The other functions
// have no record: their names and their lines are chosen, in an order the use bands ask (the order of two members,
// docs/how-to-decompile.md step 3): IncluiAvisoModoDemonstracao (fn 5583) before the sort IncluiCabecalhoEleicoes
// instantiates (fn 5582), 1543 before ImprimeDataHora (fn 1542), ImprimeTitulos (fn 3689) before
// ImprimeAberturaFechamento (fn 3688), and FormTituloPartido last, TituloPartido's first mention, so that 11182's
// ld_index is below 11181's. src/units/123-uenux2-crelatoriotesteimpressora.mk has the measurements.
// FormCabecalhoEleicao (fn 5580) and FormRodapeZeresima (fn 5579), between ImprimeSeparadorVia and DSCodigoVerificador,
// with 5580's internal helper ImprimeLinhaIgual: src/units/325-uenux2-geradores-zeresima.mk.
// ImprimeQuantidade (fn 2248), after DSCodigoVerificador: src/units/220-uenux2-fimvotacao-estados.mk.
#include "app/comum/relatorios/crelutil.h"

#include <algorithm>
#include <format>
#include <map>
#include <vector>

#include "api/gui/cpaperformbuilder.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/cpe.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/comum/relatorios/csubstituidortitulo.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

// (original lines 42-50: content not recovered)
#line 51
namespace {

std::string TituloPartido()
{
    CPartidos& partidos = CPartidos::GetInst();

    if (partidos.IsFim()) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9084, "Partido não posicionado");
    }
    const md::CPartido* partido = partidos.GetCurrent();
    const ueword numero = partido->GetNumero();
    return md::CTradutorFrase::Traduz("<PLSN>") + ": " + std::to_string(numero) + " - " + partido->GetSigla();
}
} // namespace

std::string CRelUtil::GetIDCargaFormatado(const std::string& idCarga)
{
    if (idCarga.size() <= 20) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9085, "ID de carga inválido: [" + idCarga + "]");
    }
    return idCarga.substr(0, 3) + "." + idCarga.substr(3, 3) + "." + idCarga.substr(6, 3) + "." + idCarga.substr(9, 3) +
           "." + idCarga.substr(12, 3) + "." + idCarga.substr(15, 3) + "." + idCarga.substr(18, 3) + "." +
           idCarga.substr(21);
}

namespace {
std::vector<std::string> QuebraLinhas(const ecourna::app::dados::CTituloRelatorio& titulo)
{
    std::vector<std::string> linhas =
        ecourna::api::util::CStringUtils::Split(md::CTradutorFrase::Traduz(titulo.GetTexto()), '\n');
    if (!linhas.empty() && linhas.back().empty()) {
        linhas.pop_back();
    }
    return linhas;
}
} // namespace

void CRelUtil::ImprimeTitulos(api::CPaperFormBuilder& builder,
                              const std::vector<ecourna::app::dados::CTituloRelatorio>& titulos, const std::string& uf)
{
    if (!CSubstituidorTitulo::Existe()) {
        std::map<std::string, std::string> substituicoes;
        substituicoes["<uf>"] = uf;
        CSubstituidorTitulo::CreateInst(substituicoes);
    }
    const CSubstituidorTitulo& substituidor = CSubstituidorTitulo::GetInst();
    for (size_t i = 0; i < titulos.size(); ++i) {
        const ecourna::app::dados::CTituloRelatorio& titulo = titulos[i];
        std::vector<std::string> linhas = QuebraLinhas(titulo);
        for (size_t j = 0; j < linhas.size(); ++j) {
            if (linhas[j].empty()) {
                builder.AddNewLine(1);
                continue;
            }
            builder.AddTextField(substituidor.Substitui(linhas[j]),
                                 titulo.GetEstilo() == ecourna::app::dados::CTituloRelatorio::EET_EXPANDIDO
                                     ? static_cast<api::IPaper::EStyle>(2)
                                     : static_cast<api::IPaper::EStyle>(1),
                                 titulo.GetAlinhamento() == ecourna::app::dados::CTituloRelatorio::EAT_CENTRO
                                     ? api::ALINHAMENTO_CENTRO
                                     : (titulo.GetAlinhamento() == ecourna::app::dados::CTituloRelatorio::EAT_DIREITO
                                            ? api::ALINHAMENTO_DIREITA
                                            : api::ALINHAMENTO_ESQUERDA));
        }
    }
}

void CRelUtil::ImprimeTitulos(api::CPaperFormBuilder& builder,
                              const std::vector<ecourna::app::dados::CTituloRelatorio>& titulos)
{
    ImprimeTitulos(builder, titulos, CLocal::GetInst().GetUF());
}

// (original lines 124-201: content not recovered)
#line 202
void CRelUtil::IncluiAvisoModoDemonstracao(api::CPaperFormBuilder& builder)
{
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (informacao.EhModoDemonstracao()) {
        builder.AddTextField("IMPRESSO EM MODO DEMONSTRAÇÃO", static_cast<api::IPaper::EStyle>(1),
                             api::ALINHAMENTO_CENTRO);
        builder.AddNewLine(2);
    }
}

void CRelUtil::IncluiCabecalhoPleito(api::CPaperFormBuilder& builder, const std::string& titulo,
                                     const md::CPleito& pleito)
{
    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    IncluiAvisoModoDemonstracao(builder);
    ImprimeTitulos(builder, configuracao.GetParametrosUrna().GetCabecalho());
    builder.AddNewLine(1);
    if (!titulo.empty()) {
        builder.AddTextField(titulo, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
        builder.AddNewLine(1);
    }
    if (configuracao.GetOrigem() == md::ORIGEM_COMUNITARIA) {
        builder.AddTextField("Eleições Comunitárias", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
        builder.AddNewLine(1);
    }
    builder.AddTextField(configuracao.GetNome(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(pleito.GetNome(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(pleito.GetData().Format("(DD/MM/YYYY)"), static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
}

void CRelUtil::IncluiCabecalhoEleicoes(api::CPaperFormBuilder& builder, const std::string& titulo,
                                       const bool usaPleito2)
{
    md::CPleito pleito = CConfiguracaoEleicao::GetInst().GetPleito();
    if (usaPleito2) {
        if (!CPE::Existe()) {
            CPE::CreateInst(CAppInfo::GetInst().LeGeralInterno(), FLASH_INTERNA);
        }
        if (CPE::GetInst().GetProcessoEleitoral().TemPleito2()) {
            const api::CDate hoje;
            const md::CPleito& pleito2 = CPE::GetInst().GetProcessoEleitoral().GetPleito2();
            if (pleito2.GetData() == hoje || pleito2.GetData() < hoje) {
                pleito = pleito2;
            }
        }
    }
    IncluiCabecalhoPleito(builder, titulo, pleito);
    md::TVectorEleicaoPE eleicoes = pleito.GetEleicoes();
    if (eleicoes.size() >= 2) {
        std::sort(eleicoes.begin(), eleicoes.end(), [](md::CEleicaoPE a, md::CEleicaoPE b) {
            const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
            return configuracao.GetSituacoesEleicoes(a.GetID()).GetOrdemImpressao() <
                   configuracao.GetSituacoesEleicoes(b.GetID()).GetOrdemImpressao();
        });
        for (const md::CEleicaoPE& eleicao : eleicoes) {
            builder.AddTextField(eleicao.GetNome(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
        }
        builder.AddNewLine(1);
    }
}

void CRelUtil::IncluiCabecalhoEleicoesMZS(api::CPaperFormBuilder& builder, const std::string& titulo,
                                          const TMunicipioID municipio, const TZonaID zona, const TSecaoID secao,
                                          const std::string& nomeMunicipio, const ETipoCabecalho tipo,
                                          const bool usaPleito2)
{
    IncluiCabecalhoEleicoes(builder, titulo, usaPleito2 && tipo == eCabecalhoContingencia);
    const CLocal& local = CLocal::GetInst();
    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    builder.AddTextField(std::format("{:<32s} {:05}", md::CTradutorFrase::Traduz("<MLSN>"), municipio),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(nomeMunicipio, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField(std::format("{:<33s} {:04}", md::CTradutorFrase::Traduz("<ZLSN>"), zona),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    switch (tipo) {
        case eCabecalhoSecao:
            if (configuracao.GetOrigem() != md::ORIGEM_COMUNITARIA) {
                builder.AddTextField(std::format("{:<33s} {:04}", "Local de Votação", local.GetLocalID()),
                                     static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
            }
            builder.AddTextField(std::format("{:<33s} {:04}", md::CTradutorFrase::Traduz("<SLSN>"), secao),
                                 static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
            if (local.GetQtdAgregadas()) {
                const std::string formatoQuantidade = std::format(
                    "{:<33s} {{:04}}", md::CTradutorFrase::Traduz("Quantidade de <SCPB> agregad<S|os|os|as>"));
                builder.AddTextField(FormataQtdAgregadas(formatoQuantidade), static_cast<api::IPaper::EStyle>(1),
                                     api::ALINHAMENTO_ESQUERDA);
                const std::string formatoAgregadas = md::CTradutorFrase::Traduz("<SCPN> agregad<S|os|os|as>: {}");
                builder.AddTextField(FormataAgregadas(formatoAgregadas), static_cast<api::IPaper::EStyle>(1),
                                     api::ALINHAMENTO_CENTRO);
            }
            break;
        case eCabecalhoMesaReceptora:
            builder.AddTextField(std::format("{:<34s} {:03}", "Mesa Receptora", secao / 10),
                                 static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
            builder.AddTextField(std::format("{:<34s}   {}", "Urna", secao % 10), static_cast<api::IPaper::EStyle>(1),
                                 api::ALINHAMENTO_ESQUERDA);
            break;
        case eCabecalhoContingencia:
            builder.AddTextField("Urna de contingência", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
            break;
        case eCabecalhoInvalido:
            throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9086, std::format("Tipo inválido: {}", tipo));
    }
    builder.AddNewLine(1);
}

void CRelUtil::ImprimeAberturaFechamento(api::CPaperFormBuilder& builder, const api::CDateTime& abertura,
                                         const api::CDateTime& fechamento)
{
    ImprimeDataHora(builder, abertura, "Data de abertura da UE", "Horário de abertura");
    ImprimeDataHora(builder, fechamento, "Data de fechamento da UE", "Horário de fechamento");
    builder.AddNewLine(1);
}

void CRelUtil::ImprimeDataHora(api::CPaperFormBuilder& builder, const api::CDateTime& dataHora,
                               const std::string& rotuloData, const std::string& rotuloHora)
{
    builder.AddTextField(ecourna::api::util::CStringUtils::PreencheADireita(rotuloData, ' ', 28)
                         + dataHora.GetData().Format("DD/MM/YYYY"),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(ecourna::api::util::CStringUtils::PreencheADireita(rotuloHora, ' ', 28)
                         + dataHora.GetHora().Format("  hh:mm:ss"),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

void CRelUtil::ImprimeResumoCorrespondencia(api::CPaperFormBuilder& builder,
                                            const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    builder.AddTextField("RESUMO DA CORRESPONDÊNCIA", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(FormataCodigoCargaResumido(correspondencia), static_cast<api::IPaper::EStyle>(2),
                         api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
}

void CRelUtil::ImprimeSeparadorFase(api::CPaperFormBuilder& builder, const EUrnaFase fase)
{
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    std::string separador;
    separador = GetSeparadorFase(fase);
    builder.AddTextField(separador, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
}

void CRelUtil::ImprimeSeparadorVia(api::CPaperFormBuilder& builder, unsigned int via, unsigned int totalVias)
{
    builder.AddTextField(std::format("-------------- {:02} / {:02} ---------------", via, totalVias),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
}

namespace {

void ImprimeLinhaIgual(api::CPaperFormBuilder& builder)
{
    builder.AddTextField(std::string(38, '='), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

} // namespace

std::shared_ptr<api::IForm<api::IPaper>> CRelUtil::FormCabecalhoEleicao()
{
    api::CPaperFormBuilder builder;
    ImprimeLinhaIgual(builder);
    builder.AddTextField(NomeEleicaoCorrente, api::ALINHAMENTO_CENTRO);
    ImprimeLinhaIgual(builder);
    builder.AddNewLine(1);
    return builder.Build();
}

// (original lines 374-388: content not recovered)
#line 389
std::shared_ptr<api::IForm<api::IPaper>> CRelUtil::FormRodapeZeresima(
    const std::string& separador, const std::vector<ecourna::app::dados::CTituloRelatorio>& rodape,
    const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(separador, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField("Código de identificação da carga", static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddTextField(GetIDCargaFormatado(correspondencia.GetCodigoCarga()), static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField("Ver: " + api::CStringUtils::GetVersionNumber("10.23.0.1 - DESENVOLVIMENTO"),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    ImprimeTitulos(builder, rodape);
    builder.AddNewLine(20);
    builder.AddCut();
    return builder.Build();
}

std::string CRelUtil::DSCodigoVerificador()
{
    CCalculaCV& calculo = api::CPolySingleton<CCalculaCV>::instance();
    const std::string codigo = calculo.CalculaCodigo();
    return std::format("Código Verificador: {}.{}.{}.{}", codigo.substr(0, 1), codigo.substr(1, 3), codigo.substr(4, 3),
                       codigo.substr(7, 3));
}

void CRelUtil::ImprimeQuantidade(api::CPaperFormBuilder& builder, const std::string& rotulo, ueword quantidade)
{
    builder.AddTextField(
        ecourna::api::util::CStringUtils::PreencheADireita(rotulo, ' ', 34) + std::format("{:04}", quantidade),
        static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

// (original lines 425-539: content not recovered)
#line 540
std::string CRelUtil::GetSeparadorFase(const EUrnaFase fase)
{
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (informacao.EhModoDemonstracao()) {
        return "============DEMONSTRAÇÃO==============";
    } else {
        switch (fase) {
            case FASE_SIMULADO:
                return "===============SIMULADO===============";
            case FASE_TREINAMENTO:
                return "==============TREINAMENTO=============";
            case FASE_OFICIAL:
                return "======================================";
            default:
                throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9087, std::format("Fase inválida: {}", fase));
        }
    }
}

std::shared_ptr<api::IForm<api::IPaper>> CRelUtil::FormTituloPartido()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(TituloPartido, api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

} // namespace comum
