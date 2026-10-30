#include "app/comum/gravadores/asn/cconversorhasharquivo.h"

namespace comum::asn {

CConversorHashArquivo::TEntidade CConversorHashArquivo::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_nomeArquivo(dado.GetNome());
    entidade.set_assinatura(dado.GetHash());
    return entidade;
}

} // namespace comum::asn
