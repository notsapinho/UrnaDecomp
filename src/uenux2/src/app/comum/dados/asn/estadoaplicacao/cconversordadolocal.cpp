#include "app/comum/dados/asn/estadoaplicacao/cconversordadolocal.h"

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversorlocalidadeeleitoral.h"

namespace comum::asn {

CConversorDadoLocal::TEntidade CConversorDadoLocal::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_tipoLocalVotacao() = Utils::ConverteTipoLocalVotacao(dado.GetTipoLocalVotacao());
    entidade.set_uf(dado.GetUF());
    CConversorLocalidadeEleitoral conversor;
    entidade.set_secaoCarga() = conversor.Converte(dado.GetSecaoCarga());
    return entidade;
}

CConversorDadoLocal::TDado CConversorDadoLocal::DoDesconverte(const TEntidade& entidade) const
{
    const std::string uf = entidade.get_uf();
    const ETipoLocalVotacao tipo = Utils::DesconverteTipoLocalVotacao(entidade.get_tipoLocalVotacao());
    CConversorLocalidadeEleitoral conversor;
    const md::estadoaplicacao::CLocalidadeEleitoral secaoCarga = conversor.Desconverte(entidade.get_secaoCarga());
    return TDado(uf, secaoCarga, tipo);
}

} // namespace comum::asn
