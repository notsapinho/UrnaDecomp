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

} // namespace comum::asn
