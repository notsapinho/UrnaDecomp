// comum::CImprimirExtratoCarga's out-of-line members. The reconstruction's own note: no record names this file or its
// lines; cimprimirextratocarga.h says what places the members here, src/units/123-uenux2-crelatoriotesteimpressora.mk
// what the bytes decide for ImprimeDataHoraEmissao, and src/units/296-uenux2-relatorios-impressao.mk for Imprime.
#include "app/comum/relatorios/cimprimirextratocarga.h"

#include <format>

#include "api/util/cdatetime.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/crelutil.h"

namespace comum {

void CImprimirExtratoCarga::ImprimeDataHoraEmissao(api::CPaperFormBuilder& builder) const
{
    builder.AddNewLine(1);
    builder.AddTextField("EMISSÃO DO RELATÓRIO", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::format("DATA: {:.10}       HORA: {:.8}", api::CDateTime::FormatCurrentDate("DD/MM/YYYY"),
                                     api::CDateTime::FormatCurrentTime("hh:mm:ss")),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

void CImprimirExtratoCarga::Imprime(const std::string& titulo, const std::string& via) const
{
    const md::estadoaplicacao::CDadoCorrespondencia correspondencia = GetCorrespondencia();
    const std::vector<std::string> dadosLocal = GetDadosLocal();
    const CLocal& local = CLocal::GetInst();
    api::CPaperFormBuilder builder;
    builder.AddNewLine(1);
    builder.AddCut();
    builder.AddNewLine(1);
    builder.AddNewLine(1);
    if (EhModoDemonstracao()) {
        CRelUtil::IncluiAvisoModoDemonstracao(builder);
    }
    CRelUtil::ImprimeTitulos(builder, GetCabecalho());
    builder.AddNewLine(1);
    if (EhEleicaoComunitaria()) {
        builder.AddTextField("Eleições Comunitárias", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
        builder.AddNewLine(1);
    }
    builder.AddTextField(GetNomeEleicao(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(GetPleito().GetNome(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    const std::string dataPleito = GetPleito().GetData().Format("(DD/MM/YYYY)");
    builder.AddTextField(dataPleito, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    const md::TVectorEleicaoPE& eleicoes = GetPleito().GetEleicoes();
    if (eleicoes.size() >= 2) {
        for (const md::CEleicaoPE& eleicao : eleicoes) {
            builder.AddTextField(eleicao.GetNome(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
        }
        builder.AddNewLine(1);
    }
    ImprimeSeparador(builder);
    builder.AddTextField(GetTitulo(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(GetSeparadorFase(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    ImprimeComplementoTitulo(builder);
    builder.AddTextField(std::format("UE DE {}\n\n", GetTipoUrna()), static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    InicializaTradutorFrase();
    builder.AddTextField(std::format("UF                                  {}", GetUF()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::format("{:33}{:05}", md::CTradutorFrase::Traduz("<MCSN>"), local.GetMunicipio()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(local.GetNomeMunicipio(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(std::format("{:34}{:04}", md::CTradutorFrase::Traduz("<ZCSN>"), local.GetZonaID()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    for (const std::string& linha : dadosLocal) {
        builder.AddTextField(linha, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    }
    builder.AddTextField(std::format("Código identificação UE       {:08}", correspondencia.GetNumeroInternoUrna()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::format("Código identificação MC       {:.8}", correspondencia.GetNumeroSerieFC()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField("Código de identificação carga", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(FormataCodigoCarga(correspondencia).c_str(), static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField(std::format("Data da carga               {:.10}",
                                     correspondencia.GetDataHoraCarga().GetData().Format("DD/MM/YYYY")),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(std::format("Hora da carga                 {:.8}\n",
                                     correspondencia.GetDataHoraCarga().GetHora().Format("hh:mm:ss")),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    ImprimeDataHoraEmissao(builder);
    builder.AddNewLine(1);
    builder.AddTextField("RESUMO DA CORRESPONDÊNCIA", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::format("{}\n", FormataCodigoCargaResumido(correspondencia)),
                         static_cast<api::IPaper::EStyle>(2), api::ALINHAMENTO_CENTRO);
    ImprimeComplementoCorrespondencia(builder);
    builder.AddTextField(GetSeparadorFase(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    if (!EhTreinamento()) {
        if (TemHorarioVerao()) {
            const md::CHorarioVerao& horarioVerao = GetHorarioVerao();
            const std::string inicio = FormataInicioHorarioVerao(horarioVerao);
            const std::string fim = FormataFimHorarioVerao(horarioVerao);
            builder.AddTextField("Previsão de horário de verão:", static_cast<api::IPaper::EStyle>(1),
                                 api::ALINHAMENTO_CENTRO);
            const std::string periodo = std::format("Início: {}, fim: {}.", inicio, fim);
            builder.AddTextField(periodo, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
            if (EstaEmHorarioVerao()) {
                builder.AddTextField("-> Urna em horário de verão <-", static_cast<api::IPaper::EStyle>(1),
                                     api::ALINHAMENTO_CENTRO);
            }
        } else {
            builder.AddTextField("Não existe previsão de horário de verão.", static_cast<api::IPaper::EStyle>(1),
                                 api::ALINHAMENTO_CENTRO);
        }
        builder.AddTextField(GetSeparadorFase(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    }
    if (TemQRCode()) {
        const api::CQRCodeImagePaper qrcode(GetConteudoQRCode());
        builder.AddQRCode(qrcode.GetDados());
        const std::vector<std::string> adicionais = GetConteudosQRCodeAdicionais();
        for (std::vector<std::string>::const_iterator conteudo = adicionais.begin(); conteudo != adicionais.end();
             ++conteudo) {
            builder.AddNewLine(1);
            builder.AddQRCode(api::CQRCodeImagePaper(*conteudo).GetDados());
        }
    }
    builder.AddNewLine(1);
    builder.AddTextField(std::format("Ver: {}", "10.23.0.1 - DESENVOLVIMENTO"), static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddNewLine(1);
    builder.AddTextField(GetMensagemEncerramento(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(GetMensagemCondicoes(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField(GetSeparadorFase(), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    ImprimeAssinaturas(builder);
    builder.AddCut();
    builder.AddNewLine(1);
    builder.AddNewLine(1);
    builder.AddNewLine(1);
    builder.Show(titulo, via, true);
}

} // namespace comum
