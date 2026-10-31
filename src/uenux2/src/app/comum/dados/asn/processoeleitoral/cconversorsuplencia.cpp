#include "app/comum/dados/asn/processoeleitoral/cconversorsuplencia.h"

#include "app/comum/dados/asn/processoeleitoral/cconversornomescargo.h"

namespace comum::asn {

CConversorSuplencia::TDado CConversorSuplencia::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorNomesCargo conversor;
    return TDado(entidade.get_ordem().getValue(), entidade.get_temFoto(), conversor.Desconverte(entidade.get_nomes()));
}

} // namespace comum::asn
