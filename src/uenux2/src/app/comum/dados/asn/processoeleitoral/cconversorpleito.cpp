#include "app/comum/dados/asn/processoeleitoral/cconversorpleito.h"

#include "app/comum/asn/util.h"

namespace comum::asn {

CConversorPleito::TDado CConversorPleito::DoDesconverte(const TEntidade& entidade) const
{
    const md::TPleitoID id = entidade.get_id().getValue();
    const std::string nome = entidade.get_nome();
    return TDado(id, nome, Utils::DesconverteDataJE(entidade.get_data()));
}

} // namespace comum::asn
