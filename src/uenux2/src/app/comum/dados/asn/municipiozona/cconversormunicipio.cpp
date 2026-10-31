#include "app/comum/dados/asn/municipiozona/cconversormunicipio.h"

namespace comum::asn {

CConversorMunicipio::TEntidade CConversorMunicipio::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_codigo(dado.GetCodigo());
    entidade.set_nome(dado.GetNome());
    entidade.set_capital(false);
    entidade.set_comBiometria(dado.GetComBiometria());
    return entidade;
}

CConversorMunicipio::TDado CConversorMunicipio::DoDesconverte(const TEntidade& entidade) const
{
    const md::TMunicipioID codigo = entidade.get_codigo().getValue();
    const std::string nome = entidade.get_nome();
    return TDado(codigo, nome, entidade.comBiometria_isPresent() && entidade.get_comBiometria());
}

} // namespace comum::asn
