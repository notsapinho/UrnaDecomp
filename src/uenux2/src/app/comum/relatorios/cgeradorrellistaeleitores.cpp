// The voters' list report of comum (target fn 11908 holds ImprimeListaEleitores inlined; fns 11233 and 11234 are
// the text sources it passes by table slot). The reconstruction's note, not TSE's text: the file's one record is
// SituacaoEleitor's throw (line 100, column 15); every other line, the helpers' names but SituacaoEleitor's and
// MontaCabecalho's (the lambda's RTTI), the other helpers' internal linkage and their order are chosen.
// cgeradorrellistaeleitores.h and src/units/317-uenux2-relatorios-aptos.mk say what is evidence and what is chosen.
#include "app/comum/relatorios/cgeradorrellistaeleitores.h"

#include <memory>
#include <vector>

#include "api/gui/capplication.h"
#include "api/gui/cpaperformbuilder.h"
#include "api/gui/reports/cformpart.h"
#include "api/gui/reports/creport.h"
#include "api/util/cdatetime.h"
#include "api/util/cstringutils.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/auxiliaresrelatorio.h"
#include "app/comum/relatorios/celeitoresaptos.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "app/comum/relatorios/cparteeleitores.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "app/vota/comum/votadefs.h"

namespace comum {

namespace {

const char TITULO[] = "Lista de eleitores";

std::shared_ptr<api::IReportPart> MontaCabecalho()
{
    const CLocal& local = CLocal::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const api::CDateTime agora = api::CDateTime::Now();
    api::CPaperFormBuilder builder;
    CRelUtil::IncluiCabecalhoEleicoesMZS(builder, TITULO, local.GetMunicipio(), local.GetZonaID(),
                                         local.GetSecaoID(), local.GetNomeMunicipio(), CRelUtil::eCabecalhoSecao,
                                         false);
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

std::string CabecalhoEleitores()
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
    const std::string situacao = "Situação";
    const std::string espacos(30 - identificador.size(), ' ');
    return identificador + espacos + situacao;
}

// (original lines 80-95: content not recovered)
#line 96
std::string SituacaoEleitor()
{
    const CEleitorDetalhe* detalhe = CEleitores::GetInst().GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9068, "Eleitor não posicionado");
    }
    const md::CEleitorDecorator& eleitor = detalhe->GetEleitor();
    std::vector<std::string> situacoes;
    if (eleitor.TemBiometria()) {
        situacoes.push_back("BIO");
    }
    if (!detalhe->SemImpedimento()) {
        situacoes.push_back("IMP");
    }
    if (eleitor.NecessitaAudio()) {
        situacoes.push_back("AUD");
    }
    if (eleitor.IsTTE()) {
        situacoes.push_back("TTE");
    }
    const md::CEleitorIdentidade identidade = eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador());
    const std::string identificador = md::FormataIdentificador(identidade);
    const std::string situacao = api::Join(situacoes, "-");
    const std::string espacos(38 - (identificador.size() + situacao.size()), ' ');
    return identificador + espacos + situacao;
}

std::shared_ptr<api::IReportPart> MontaTitulos()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(&CabecalhoEleitores, api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    return std::make_shared<api::CFormPart>(builder.Build());
}

std::shared_ptr<api::IReportPart> MontaEleitores()
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(&SituacaoEleitor, api::ALINHAMENTO_ESQUERDA);
    return std::make_shared<CParteEleitores>(builder.Build());
}

std::shared_ptr<api::IReportPart> MontaLegenda()
{
    api::CPaperFormBuilder builder;
    builder.AddNewLine(1);
    vota::AdicionaSeparador(builder, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("AUD: Áudio", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("BIO: Biometria", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("IMP: Impedido", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("TTE: Transferência Temporária", static_cast<api::IPaper::EStyle>(1),
                         api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    return std::make_shared<api::CFormPart>(builder.Build());
}

std::shared_ptr<api::IReportPart> MontaRodape()
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
    builder.AddNewLine(2);
    builder.AddCut();
    builder.AddNewLine(4);
    return std::make_shared<api::CFormPart>(builder.Build());
}

} // namespace

// comum::CParteEleitores's constructor (cparteeleitores.h; Imprime, the key function, is in cparteeleitores.cpp),
// defined in this file, its one caller's. Fn 11908 holds it inlined by binaryen (its 16-byte frame inside) and stores
// the part's member through the control block, which binaryen gives from an object that drops the constructor's result;
// docs/reference/facts/codegen.md C6: a call of the C1 alias of a constructor the TU defines drops it.
// src/units/317-uenux2-relatorios-aptos.mk has the measurements. Its place in this file is chosen.
CParteEleitores::CParteEleitores(std::shared_ptr<api::IForm<api::IPaper>> form)
    : m_eleitor(std::make_shared<api::CFormPart>(std::move(form)))
{
}

void ImprimeListaEleitores(const std::string& titulo, const std::string& via)
{
    const api::CReport relatorio({MontaCabecalho(), MontaTitulos(), MontaEleitores(), MontaLegenda(), MontaRodape()});
    relatorio.Imprime(titulo, via);
}

} // namespace comum
