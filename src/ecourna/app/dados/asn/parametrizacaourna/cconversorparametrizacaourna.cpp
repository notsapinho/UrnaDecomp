#include "ecourna/app/dados/asn/parametrizacaourna/cconversorparametrizacaourna.hpp"

#include "ecourna/app/dados/asn/cconversorcabecalhoentidade.hpp"
#include "ecourna/app/dados/asn/parametrizacaourna/cconversorparametrosurna.hpp"

namespace ecourna::app::dados::asn {

CConversorParametrizacaoUrna::TEntidade CConversorParametrizacaoUrna::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    CConversorCabecalhoEntidade conversorCabecalho;
    entidade.set_cabecalho() = conversorCabecalho.Converte(dado.GetCabecalho());
    CConversorParametrosUrna conversorParametros;
    entidade.set_parametros() = conversorParametros.Converte(dado.GetParametros());
    return entidade;
}

CConversorParametrizacaoUrna::TDado CConversorParametrizacaoUrna::DoDeconverte(const TEntidade& entidade) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    CConversorParametrosUrna conversorParametros;
    const CCabecalhoEntidade cabecalho = conversorCabecalho.Deconverte(entidade.get_cabecalho());
    const CParametrosUrna parametros = conversorParametros.Deconverte(entidade.get_parametros());
    return TDado(cabecalho, parametros);
}

} // namespace ecourna::app::dados::asn
