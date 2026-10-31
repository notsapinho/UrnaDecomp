#include "ecourna/app/dados/asn/cconversoridentificacaosecaoeleitoral.hpp"

#include "ecourna/app/dados/asn/cconversormunicipiozona.hpp"

namespace ecourna::app::dados::asn {

CConversorIdentificacaoSecaoEleitoral::TEntidade CConversorIdentificacaoSecaoEleitoral::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    CConversorMunicipioZona conversorMunicipioZona;
    const ModuloTiposEleitorais::MunicipioZona municipioZona = conversorMunicipioZona.Converte(dado.GetMunicipioZona());
    entidade.set_municipioZona() = municipioZona;
    entidade.set_local(dado.GetLocal());
    entidade.set_secao(dado.GetSecao());
    return entidade;
}

CConversorIdentificacaoSecaoEleitoral::TDado CConversorIdentificacaoSecaoEleitoral::DoDeconverte(const TEntidade& entidade) const
{
    CConversorMunicipioZona conversorMunicipioZona;
    return TDado(conversorMunicipioZona.Deconverte(entidade.get_municipioZona()), entidade.get_local().getValue(),
                 entidade.get_secao().getValue());
}

} // namespace ecourna::app::dados::asn
