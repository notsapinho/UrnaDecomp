#include "ecourna/app/dados/asn/resultadournacadastro/cconversorcomparecimentosecao.hpp"

#include "ecourna/app/dados/asn/cconversoridentificacaosecaoeleitoral.hpp"
#include "ecourna/app/dados/asn/resultadournacadastro/cconversorestadocomparecimento.hpp"
#include "ecourna/app/dados/asn/sequenciaasn.hpp"

namespace ecourna::app::dados::asn {

CConversorComparecimentoSecao::TEntidade CConversorComparecimentoSecao::DoConverte(const TDado& dado) const
{
    CConversorIdentificacaoSecaoEleitoral conversorIdentificacao;
    CConversorEstadoComparecimento conversorEstado;
    TEntidade entidade;
    entidade.set_identificacao() = conversorIdentificacao.Converte(dado.GetIdentificacao());
    entidade.set_eleitores() = ConverteSequencia(dado.GetEleitores(), conversorEstado);
    return entidade;
}

CConversorComparecimentoSecao::TDado CConversorComparecimentoSecao::DoDeconverte(const TEntidade& entidade) const
{
    CConversorEstadoComparecimento conversorEstado;
    CConversorIdentificacaoSecaoEleitoral conversorIdentificacao;
    const CIdentificacaoSecaoEleitoral identificacao = conversorIdentificacao.Deconverte(entidade.get_identificacao());
    return TDado(identificacao, DeconverteSequencia(entidade.get_eleitores(), conversorEstado));
}

} // namespace ecourna::app::dados::asn
