#include "ecourna/app/dados/asn/federacoes/cconversorfederacoes.hpp"

#include "ecourna/app/dados/asn/cconversorcabecalhoentidade.hpp"
#include "ecourna/app/dados/asn/federacoes/cconversorfederacao.hpp"
#include "ecourna/app/dados/asn/sequenciaasn.hpp"

namespace ecourna::app::dados::asn {

CConversorFederacoes::TEntidade CConversorFederacoes::DoConverte(const TDado& dado) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    CConversorFederacao conversorFederacao;
    TEntidade entidade;
    entidade.set_cabecalho() = conversorCabecalho.Converte(dado.GetCabecalho());
    if (dado.GetFederacoes().empty()) {
        entidade.omit_federacoes();
    } else {
        entidade.set_federacoes(ConverteSequencia(dado.GetFederacoes(), conversorFederacao));
    }
    return entidade;
}

CConversorFederacoes::TDado CConversorFederacoes::DoDeconverte(const TEntidade& entidade) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    CConversorFederacao conversorFederacao;
    const CCabecalhoEntidade cabecalho = conversorCabecalho.Deconverte(entidade.get_cabecalho());
    TVectorFederacao federacoes;
    if (entidade.federacoes_isPresent()) {
        federacoes = DeconverteSequencia(entidade.get_federacoes(), conversorFederacao);
    }
    return TDado(cabecalho, federacoes);
}

} // namespace ecourna::app::dados::asn
