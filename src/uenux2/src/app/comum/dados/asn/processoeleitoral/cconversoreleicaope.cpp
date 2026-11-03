// comum::asn::CConversorEleicaoPE::DoDesconverte (target fn 11371). The reconstruction's own note: no record names this
// file (its records are md::CEleicaoPE's, in md/processoeleitoral/celeicaope.cpp); the path is the header's, and the
// function's line is a choice (src/units/299-uenux2-cqrcodeds-processoeleitoral.mk says what the bytes decide).
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"

#include <algorithm>
#include <iterator>

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorcargo.h"

namespace comum::asn {

CConversorEleicaoPE::TDado CConversorEleicaoPE::DoDesconverte(const TEntidade& entidade) const
{
    const std::string& nome = entidade.get_nome();
    const unsigned int idPleito = entidade.get_idPleito().getValue();
    const md::TEleicaoID id = entidade.get_cabecalho().get_idEleitoral().get_idEleicao().getValue();
    const md::ETipoAbrangencia abrangencia = Utils::DesconverteAbrangencia(entidade.get_abrangencia());
    const md::TEleicaoID idEleicaoPleito2 =
        entidade.hasOptionalField(TEntidade::e_idEleicaoPleito2) ? entidade.get_idEleicaoPleito2().getValue() : 0;
    md::TVectorCargo cargos;
    const CConversorCargo conversorCargo(abrangencia);
    std::transform(entidade.get_cargos().begin(), entidade.get_cargos().end(), std::back_inserter(cargos),
                   [&conversorCargo](const auto& cargo) { return conversorCargo.Desconverte(cargo); });
    std::vector<unsigned int> municipios;
    std::transform(entidade.get_municipios().begin(), entidade.get_municipios().end(), std::back_inserter(municipios),
                   [](const auto& municipio) { return municipio.getValue(); });
    return TDado(id, idPleito, idEleicaoPleito2, nome, abrangencia, cargos, municipios);
}

} // namespace comum::asn
