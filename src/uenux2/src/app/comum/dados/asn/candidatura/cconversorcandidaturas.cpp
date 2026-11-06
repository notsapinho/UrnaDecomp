// Reconstruction: comum::asn::CConversorCandidaturas::DoDesconverte (target fn 11445) and the function that reads one
// list of a party's candidacies (fn 5710, which holds IConversorASN<ModuloCandidatos::Candidatura, ...>::Desconverte
// inlined by binaryen: its frame opens inside 5710's loop). No record names this file or a line of it: the order of the
// two definitions and every line are a choice. The static_cast to ModuloCandidatos::Candidatura is forced by that
// class's chosen base (ModuloCandidatos.h): it generates no code. 159-uenux2-iconversorasn-defaults.mk has the rest.
#include "app/comum/dados/asn/candidatura/cconversorcandidaturas.h"

#include "app/comum/asn/cconversorcodigocargoconsulta.h"
#include "app/comum/dados/asn/candidatura/cconversorcandidatura.h"

namespace comum::asn {

void DesconverteCandidaturas(std::vector<md::CCandidatura>& candidaturas, const CConversorCandidatura& conversor,
                             const ModuloTiposResultadosEcoUrna::CandidatosAptos& lista)
{
    for (size_t i = 0; i < lista.size(); ++i) {
        candidaturas.push_back(conversor.Desconverte(static_cast<const ModuloCandidatos::Candidatura&>(lista[i])));
    }
}

CConversorCandidaturas::TDado CConversorCandidaturas::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorCodigoCargoConsulta conversorCodigo;
    TDado candidaturas;
    for (size_t i = 0; i < entidade.get_cargos().size(); ++i) {
        const ModuloCandidatos::CandidatosPorCargos& cargo = entidade.get_cargos()[i];
        const md::TCargoID idCargo = conversorCodigo.Desconverte(cargo.get_cargo());
        if (cargo.partidos_isPresent()) {
            for (size_t j = 0; j < cargo.get_partidos().size(); ++j) {
                const ModuloTiposResultadosEcoUrna::CandidatoPorPartido& partido = cargo.get_partidos()[j];
                const TPartidoID idPartido = partido.get_partido().getValue();
                DesconverteCandidaturas(candidaturas, CConversorCandidatura(idCargo, idPartido, true),
                                        partido.get_candidatosAptos());
                DesconverteCandidaturas(candidaturas, CConversorCandidatura(idCargo, idPartido, false),
                                        partido.get_candidatosInaptos());
            }
        }
    }
    return candidaturas;
}

} // namespace comum::asn
