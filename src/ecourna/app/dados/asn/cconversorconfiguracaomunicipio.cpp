#include "ecourna/app/dados/asn/cconversorconfiguracaomunicipio.hpp"

#include "ecourna/app/dados/asn/cconversorhorariosurna.hpp"

namespace ecourna::app::dados::asn {

CConversorConfiguracaoMunicipio::TEntidade CConversorConfiguracaoMunicipio::DoConverte(const TDado& dado) const
{
    CConversorHorariosUrna conversorHorarios;
    TEntidade entidade;
    entidade.set_codigoMunicipio() = TEntidade::codigoMunicipio::value_type(dado.GetCodigoMunicipio());
    entidade.set_horariosUrna() = conversorHorarios.Converte(dado.GetHorariosUrna());
    return entidade;
}

CConversorConfiguracaoMunicipio::TDado CConversorConfiguracaoMunicipio::DoDeconverte(const TEntidade& entidade) const
{
    CConversorHorariosUrna conversorHorarios;
    return TDado(entidade.get_codigoMunicipio().getValue(), conversorHorarios.Deconverte(entidade.get_horariosUrna()));
}

} // namespace ecourna::app::dados::asn
