// Reconstruction: comum::asn::CConversorHistoricoVotoImpresso::DoConverte (target fn 10276), the class's only override
// and so its key function: this object emits the vtable, with the base's default DoDesconverte (fn 10275). No record
// names this file: its path is the header's (cconversorhistoricovotoimpresso.h).
#include "app/comum/gravadores/asn/cconversorhistoricovotoimpresso.h"

#include "app/comum/asn/util.h"

namespace comum::asn {

CConversorHistoricoVotoImpresso::TEntidade CConversorHistoricoVotoImpresso::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_idImpressoraVotos(dado.GetIdImpressoraVotos());
    entidade.set_idRepositorioVotos(dado.GetIdRepositorioVotos());
    entidade.set_dataHoraLigamento() = Utils::ConverteDataHoraJE(dado.GetDataHoraLigamento());
    return entidade;
}

} // namespace comum::asn
