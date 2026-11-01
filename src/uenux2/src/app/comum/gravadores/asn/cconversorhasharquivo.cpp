#include "app/comum/gravadores/asn/cconversorhasharquivo.h"

namespace comum::asn {

CConversorHashArquivo::TDado CConversorHashArquivo::DoDesconverte(const TEntidade& entidade) const
{
    const std::string nome = entidade.get_nomeArquivo();
    const std::string hash = entidade.get_assinatura();
    return TDado(nome, hash);
}

CConversorHashArquivo::TEntidade CConversorHashArquivo::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_nomeArquivo(dado.GetNome());
    entidade.set_assinatura(dado.GetHash());
    return entidade;
}

} // namespace comum::asn
