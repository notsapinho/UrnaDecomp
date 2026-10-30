// Reconstruction: comum::asn::CConversorLocalidadeEleitoral (target fns 11388, 11389). No record names this file: its
// name is the class's, and its directory the family's, as for cconversornumviasimpressasrelatorios.cpp beside it.
#include "app/comum/dados/asn/estadoaplicacao/cconversorlocalidadeeleitoral.h"

namespace comum::asn {

CConversorLocalidadeEleitoral::TEntidade CConversorLocalidadeEleitoral::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_municipio(dado.GetMunicipio());
    entidade.set_zona(dado.GetZona());
    entidade.set_secao(dado.GetSecao());
    return entidade;
}

CConversorLocalidadeEleitoral::TDado CConversorLocalidadeEleitoral::DoDesconverte(const TEntidade& entidade) const
{
    return TDado(entidade.get_municipio().getValue(), entidade.get_zona().getValue(), entidade.get_secao().getValue());
}

} // namespace comum::asn
