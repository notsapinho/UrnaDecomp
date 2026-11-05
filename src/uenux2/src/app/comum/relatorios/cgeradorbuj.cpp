// comum::CGeradorBUJ: the forms of the report of the justified voters and their printing to a file (cgeradorbuj.h).
// The reconstruction's note, not TSE's text: the file's one record is GeraBUJ's default argument of
// api::CPolySingleton<api::IPaperRelatorios>::instance (line 189, column 29); the helpers, their names, their internal
// linkage, their order and every other line are chosen. src/units/372-uenux2-relatorios-gerarelatorios.mk has the evidence.
#include "app/comum/relatorios/cgeradorbuj.h"

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "api/gui/cdatatextfmt.h"
#include "api/gui/cpaperformbuilder.h"
#include "api/gui/iform.h"
#include "api/gui/ipaperrelatorios.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "api/util/csynchronizer.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/justificativa/cjustificador.h"
#include "app/comum/relatorios/crelutil.h"

namespace comum {

namespace {

std::shared_ptr<api::IForm<api::IPaper>> MontaCabecalho(const std::string& titulo, uedword municipio, ueword zona,
    ueword secao, const std::string& nomeMunicipio, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    api::CPaperFormBuilder builder;
    CRelUtil::IncluiCabecalhoEleicoesMZS(builder, titulo, municipio, zona, secao, nomeMunicipio, CRelUtil::eCabecalhoSecao,
                                         false);
    builder.AddTextField(&GetIdentificacaoUrna, api::ALINHAMENTO_ESQUERDA);
    if (CAppInfo::GetInst().TemVota(std::as_const(CAppInfo::GetInst()).GetGeral().GetDadoCarga().GetTurno())) {
        const api::CDateTime inicio = CAppInfo::GetInst().GetVota().GetDtHrInicioAquisicao();
        const api::CDateTime fim = CAppInfo::GetInst().GetVota().GetDtHrFimAquisicao();
        CRelUtil::ImprimeAberturaFechamento(builder, inicio, fim);
    }
    CRelUtil::ImprimeResumoCorrespondencia(builder, correspondencia);
    return builder.Build();
}

std::shared_ptr<api::IForm<api::IPaper>> MontaTotais(const std::string& separadorFase)
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(separadorFase, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField(&CJustificadorDadoQuantidade::Text, "{:05} Justificativas");
    builder.AddNewLine(1);
    return builder.Build();
}

std::shared_ptr<api::IForm<api::IPaper>> MontaJustificativa()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(&CJustificadorDadoTitulo::Text, api::ALINHAMENTO_ESQUERDA);
    return builder.Build();
}

std::shared_ptr<api::IForm<api::IPaper>> MontaRodape(const std::string& separadorFase,
                                                     const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(1);
    builder.AddTextField(separadorFase, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField("Código de identificação da carga", static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_CENTRO);
    builder.AddTextField(CRelUtil::GetIDCargaFormatado(correspondencia.GetCodigoCarga()),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField(std::format("Ver: {}", api::CStringUtils::GetVersionNumber("10.23.0.1 - DESENVOLVIMENTO")),
                         static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField("ASSINATURAS:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(1);
    builder.AddTextField("PRESIDENTE:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(2);
    builder.AddTextField("MESÁRIOS:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(3);
    builder.AddTextField("FISCAIS:", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(20);
    builder.AddCut();
    return builder.Build();
}

} // namespace

CGeradorBUJ::CGeradorBUJ(const std::string& titulo, const std::string& separadorFase, uedword municipio, ueword zona,
                         ueword secao, const std::string& nomeMunicipio,
                         const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
    : m_cabecalho(MontaCabecalho(titulo, municipio, zona, secao, nomeMunicipio, correspondencia)),
      m_totais(MontaTotais(separadorFase)),
      m_justificativa(MontaJustificativa()),
      m_rodape(MontaRodape(separadorFase, correspondencia))
{
}

// (original lines 103-186: content not recovered)
#line 187
void CGeradorBUJ::GeraBUJ(const std::string& arquivo)
{
    api::IPaper& impresso = api::CPolySingleton<api::IPaperRelatorios>::instance();
    impresso.StartReportFile(arquivo);
    m_cabecalho->Slot2();
    m_totais->Slot2();
    CJustificador& justificador = CJustificador::GetInst();
    for (justificador.Reset(); !justificador.IsFim(); justificador.Next()) {
        m_justificativa->Slot2();
    }
    m_rodape->Slot2();
    impresso.EndReportFile();
    api::CSynchronizer::GetInst().Sync();
}

} // namespace comum
