// comum::CRelatorioTesteImpressora. The reconstruction's own note: the blank lines stand for text not recovered. The
// one record of this file is line 173, a throw of comum::(anonymous namespace)::ConverteTipoAlimentacao, which
// GetDadosLocal (fn 11188, not reconstructed) holds inlined; that line stays blank. The members written here are
// defined in the order their target functions run in the link (use band 1, fns 11202 down to 11189 before 11188, then
// 11187 down to 11183), and their lines are a choice. src/units/123-uenux2-crelatoriotesteimpressora.mk lists them.
#include "app/comum/relatorios/crelatoriotesteimpressora.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/chv.h"
#include "app/comum/dados/cpe.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/crelutil.h"

namespace comum {

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

md::estadoaplicacao::CDadoCorrespondencia CRelatorioTesteImpressora::GetCorrespondencia() const
{
    return CAppInfo::GetInst().GetGeral().GetCorrespondencia();
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

// <stubs>
// f5586 · 205 B · unmatched · placement: link order · name unknown
// ? f5586(i32) { ... }
// </stubs>
