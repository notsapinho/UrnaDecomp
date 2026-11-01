#include "app/comum/asn/cconversorcodigocargoconsulta.h"

namespace comum::asn {

CConversorCodigoCargoConsulta::TEntidade CConversorCodigoCargoConsulta::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    if (dado < 25) {
        entidade.select_cargoConstitucional() =
            static_cast<TEntidade::cargoConstitucional::value_type::NamedNumber>(dado);
    } else {
        entidade.select_numeroCargoConsultaLivre() = dado;
    }
    return entidade;
}

CConversorCodigoCargoConsulta::TDado CConversorCodigoCargoConsulta::DoDesconverte(const TEntidade& entidade) const
{
    if (entidade.cargoConstitucional_isSelected()) {
        return entidade.get_cargoConstitucional().asInt();
    }
    return entidade.get_numeroCargoConsultaLivre().getValue();
}

} // namespace comum::asn
