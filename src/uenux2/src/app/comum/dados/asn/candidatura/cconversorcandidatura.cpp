// Reconstruction: comum::asn::CConversorCandidatura's constructor (target fn 5712) and DoDesconverte (fn 11448). No
// record names this file or a line of it: the order of the two definitions and every line are a choice. The static_casts
// to ModuloCandidatos::DadosCandidato are forced by that class's chosen base (ModuloCandidatos.h): they generate no code.
// 159-uenux2-iconversorasn-defaults.mk has the rest.
#include "app/comum/dados/asn/candidatura/cconversorcandidatura.h"

#include "app/comum/dados/asn/candidatura/cconversordadoscandidato.h"

namespace comum::asn {

CConversorCandidatura::CConversorCandidatura(md::TCargoID cargo, TPartidoID partido, bool apto)
    : m_cargo(cargo), m_partido(partido), m_apto(apto)
{
}

CConversorCandidatura::TDado CConversorCandidatura::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorDadosCandidato conversor(m_apto);
    const TCandidatoID numero = entidade.get_numero().getValue();
    const md::CDadosCandidato titular =
        conversor.Desconverte(static_cast<const ModuloCandidatos::DadosCandidato&>(entidade.get_titular()));
    if (entidade.suplentesVices_isPresent()) {
        std::vector<md::CDadosCandidato> suplentes;
        for (size_t i = 0; i < entidade.get_suplentesVices().size(); ++i) {
            suplentes.push_back(conversor.Desconverte(
                static_cast<const ModuloCandidatos::DadosCandidato&>(entidade.get_suplentesVices().at(i))));
        }
        return TDado(m_cargo, m_partido, numero, titular, suplentes);
    }
    return TDado(m_cargo, m_partido, numero, titular, std::vector<md::CDadosCandidato>());
}

} // namespace comum::asn
