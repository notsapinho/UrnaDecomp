#include "app/comum/dados/asn/cconversorpartido.h"

namespace comum::asn {

CConversorPartido::TEntidade CConversorPartido::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_nome(dado.GetNome());
    entidade.set_sigla(dado.GetSigla());
    entidade.set_numero(dado.GetNumero());
    return entidade;
}

CConversorPartido::TDado CConversorPartido::DoDesconverte(const TEntidade& entidade) const
{
    const std::string nome = entidade.get_nome();
    const std::string sigla = entidade.get_sigla();
    return md::CPartido(entidade.get_numero().getValue(), sigla, nome);
}

} // namespace comum::asn
