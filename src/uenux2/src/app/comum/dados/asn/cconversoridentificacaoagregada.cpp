#include "app/comum/dados/asn/cconversoridentificacaoagregada.h"

#include "app/comum/asn/util.h"

namespace comum::asn {

CConversorIdentificacaoAgregada::TEntidade CConversorIdentificacaoAgregada::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_numero(dado.GetNumero());
    entidade.set_tipoLocalOrigem() = Utils::ConverteTipoLocalVotacao(dado.GetTipoLocalOrigem());
    return entidade;
}

CConversorIdentificacaoAgregada::TDado CConversorIdentificacaoAgregada::DoDesconverte(const TEntidade& entidade) const
{
    return TDado(entidade.get_numero().getValue(), Utils::DesconverteTipoLocalVotacao(entidade.get_tipoLocalOrigem()));
}

} // namespace comum::asn
