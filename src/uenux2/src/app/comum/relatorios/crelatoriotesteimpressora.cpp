// comum::CRelatorioTesteImpressora. The reconstruction's own note: the blank lines stand for text not recovered. The
// one record of this file is line 173, CPolySingleton<IPower>::instance()'s default std::source_location in
// comum::(anonymous namespace)::ConverteTipoAlimentacao, which GetDadosLocal (fn 11188) holds inlined. The members are
// defined in the order their target functions run in the link (use band 1, fns 11202 down to 11189, then 11188, then
// 11187 down to 11183), and their lines are a choice. src/units/123-uenux2-crelatoriotesteimpressora.mk lists them.
#include "app/comum/relatorios/crelatoriotesteimpressora.h"

#include <format>
#include <vector>

#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/chv.h"
#include "app/comum/dados/cpe.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/crelutil.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

CRelatorioTesteImpressora::CRelatorioTesteImpressora()
{
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    m_usaPleito2 = false;
    if (geral.GetDadoCarga().GetTipoUrna() == eUrnaContingencia) {
        if (!CPE::Existe()) {
            CPE::CreateInst(geral, FLASH_INTERNA);
        }
        if (CPE::GetInst().GetProcessoEleitoral().TemPleito2()) {
            const api::CDate hoje;
            const api::CDate& data = CPE::GetInst().GetProcessoEleitoral().GetPleito2().GetData();
            if (data == hoje || data < hoje) {
                m_usaPleito2 = true;
            }
        }
    }
}

bool CRelatorioTesteImpressora::TemHorarioVerao() const
{
    return CHV::GetInst().TemHorarioVerao();
}

bool CRelatorioTesteImpressora::EhTreinamento() const
{
    return CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() == FASE_TREINAMENTO;
}

const md::CHorarioVerao& CRelatorioTesteImpressora::GetHorarioVerao() const
{
    return CHV::GetInst().GetHorarioVerao();
}

bool CRelatorioTesteImpressora::EstaEmHorarioVerao() const
{
    const md::CHorarioVerao& horarioVerao = CHV::GetInst().GetHorarioVerao();
    const api::CDateTime agora = api::CDateTime::Now();
    return horarioVerao.Contem(agora.GetData());
}

md::estadoaplicacao::CDadoCorrespondencia CRelatorioTesteImpressora::GetCorrespondencia() const
{
    return CAppInfo::GetInst().GetGeral().GetCorrespondencia();
}

void CRelatorioTesteImpressora::InicializaTradutorFrase() const
{
    const ecourna::app::dados::CParametrosUrna& parametros = CConfiguracaoEleicao::GetInst().GetParametrosUrna();
    const std::map<char, ecourna::app::dados::CLabelParametrizado> labels = {{'M', parametros.GetLabelMunicipio()},
                                                                              {'Z', parametros.GetLabelZona()},
                                                                              {'S', parametros.GetLabelSecao()},
                                                                              {'P', parametros.GetLabelPartido()}};
    md::CTradutorFrase::SetLabels(labels);
}

const ecourna::app::dados::CParametrosUrna::TVectorTituloRelatorio& CRelatorioTesteImpressora::GetCabecalho() const
{
    return CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetCabecalho();
}

bool CRelatorioTesteImpressora::EhEleicaoComunitaria() const
{
    return CConfiguracaoEleicao::GetInst().GetOrigem() == md::ORIGEM_COMUNITARIA;
}

bool CRelatorioTesteImpressora::EhModoDemonstracao() const
{
    return CInformacaoEleicao(CConfiguracaoEleicao::GetInst().GetParametrosUrna()).EhModoDemonstracao();
}

std::string CRelatorioTesteImpressora::GetNomeEleicao() const
{
    return CConfiguracaoEleicao::GetInst().GetNome();
}

const md::CPleito& CRelatorioTesteImpressora::GetPleito() const
{
    if (m_usaPleito2 && CPE::GetInst().GetProcessoEleitoral().TemPleito2()) {
        return CPE::GetInst().GetProcessoEleitoral().GetPleito2();
    }
    return CConfiguracaoEleicao::GetInst().GetPleito();
}

std::string CRelatorioTesteImpressora::GetTipoUrna() const
{
    switch (CAppInfo::GetInst().GetGeral().GetDadoCarga().GetTipoUrna()) {
    case eUrnaVota:
    case eUrnaContingenciaVota:
    case eUrnaContingenciaVotaRecupera:
        return "VOTAÇÃO";
    default:
        return "CONTINGÊNCIA";
    }
}

std::string CRelatorioTesteImpressora::GetUF() const
{
    return CAppInfo::GetInst().GetGeral().GetDadoLocal().GetUF();
}

namespace {

std::string FormataParametro(const std::string& nome, const std::string& valor)
{
    std::string linha = nome;
    linha += ecourna::api::util::CStringUtils::PreencheAEsquerda(valor, ' ', 38 - nome.size());
    return linha;
}

std::string ConverteTipoLocal()
{
    switch (CLocal::GetInst().GetTipoLocalVotacao()) {
    case LOCAL_VOTACAO_NORMAL:
        return "Normal";
    case LOCAL_VOTACAO_EM_TRANSITO:
        return "Voto em Trânsito";
    case LOCAL_VOTACAO_PRESO_PROVISORIO:
        return "Preso provisório";
    case LOCAL_VOTACAO_TEMPORARIO:
        return "Temporário";
    default:
        return "Inválido";
    }
}

// (original lines 151-170: content not recovered)
#line 171
std::string ConverteTipoAlimentacao()
{
    auto& ipower = api::CPolySingleton<api::IPower>::instance();
    switch (ipower.Fonte()) {
    case 0:
        return "R. Elétrica";
    case 1:
        return "B. Interna";
    case 2:
        return "B. Externa";
    default:
        return "Não identificada";
    }
}

} // namespace

std::vector<std::string> CRelatorioTesteImpressora::GetDadosLocal() const
{
    std::vector<std::string> linhas;
    const CLocal& local = CLocal::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const EUrnaTipo tipo = geral.GetDadoCarga().GetTipoUrna();
    if (tipo == eUrnaVota || tipo == eUrnaContingenciaVota || tipo == eUrnaContingenciaVotaRecupera) {
        const TSecaoID secao = local.GetSecaoID();
        if (geral.GetDadoCarga().GetFase() == FASE_OFICIAL) {
            linhas.push_back(std::format("Local                             {:04}", local.GetLocalID()));
        }
        InicializaTradutorFrase();
        const std::string rotuloSecao =
            ecourna::api::util::CStringUtils::PreencheADireita(md::CTradutorFrase::Traduz("<SCSN>"), ' ', 34);
        linhas.push_back(std::format("{}{:04}", rotuloSecao, secao));
        if (local.GetQtdAgregadas()) {
            const std::string linha = std::format("{:<33s} {:04}",
                md::CTradutorFrase::Traduz("Quantidade de <SCPB> agregad<S|os|os|as>"), local.GetQtdAgregadas());
            linhas.push_back(linha);
            const std::string formato = md::CTradutorFrase::Traduz("<SCPN> agregad<S|os|os|as>: {}");
            linhas.push_back(FormataAgregadas(formato));
        }
        const std::string rotuloTipo = "Tipo de local";
        const std::string tipoLocal = ConverteTipoLocal();
        linhas.push_back(FormataParametro(rotuloTipo, tipoLocal));
        const std::string rotuloBiometria = "Local com biometria";
        const std::string biometria = local.UrnaBiometrica() ? "Sim" : "Não";
        linhas.push_back(FormataParametro(rotuloBiometria, biometria));
    }
    const std::string rotuloAlimentacao = "Tipo de alimentação";
    const std::string alimentacao = ConverteTipoAlimentacao();
    linhas.push_back(FormataParametro(rotuloAlimentacao, alimentacao));
    return linhas;
}


std::string CRelatorioTesteImpressora::GetTitulo() const
{
    return "ESTADO DA URNA";
}

std::string CRelatorioTesteImpressora::GetMensagemEncerramento() const
{
    return "URNA OPERANDO EM PERFEITAS";
}

std::string CRelatorioTesteImpressora::GetMensagemCondicoes() const
{
    return "CONDIÇÕES DE FUNCIONAMENTO\n";
}

std::string CRelatorioTesteImpressora::GetSeparadorFase() const
{
    return CRelUtil::GetSeparadorFase(CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase());
}

} // namespace comum
