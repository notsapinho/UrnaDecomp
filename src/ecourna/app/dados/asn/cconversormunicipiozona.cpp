#include "ecourna/app/dados/asn/cconversormunicipiozona.hpp"

namespace ecourna::app::dados::asn {

ModuloTiposEleitorais::MunicipioZona CConversorMunicipioZona::DoConverte(const CMunicipioZona& dado) const
{
    TEntidade entidade;
    entidade.set_municipio(dado.GetMunicipio());
    entidade.set_zona(dado.GetZona());
    return entidade;
}

CMunicipioZona CConversorMunicipioZona::DoDeconverte(const ModuloTiposEleitorais::MunicipioZona& entidade) const
{
    return CMunicipioZona(entidade.get_municipio().getValue(), entidade.get_zona().getValue());
}

} // namespace ecourna::app::dados::asn
