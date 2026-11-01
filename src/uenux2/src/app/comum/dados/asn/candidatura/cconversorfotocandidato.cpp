// Reconstruction: comum::asn::CConversorFotoCandidato::DoDesconverte (target fn 11440), the class's only override and so
// its key function: this object emits the vtable, with the base's default DoConverte (fn 11439). No record names this
// file: its path is the header's (cconversorfotocandidato.h).
#include "app/comum/dados/asn/candidatura/cconversorfotocandidato.h"

#include "ecourna/app/dados/asn/cconversorfoto.hpp"

namespace comum::asn {

CConversorFotoCandidato::TDado CConversorFotoCandidato::DoDesconverte(const TEntidade& entidade) const
{
    const std::string codigoCandidato = entidade.get_codigoCandidato();
    const ecourna::app::dados::asn::CConversorFoto conversorFoto;
    return TDado(codigoCandidato, conversorFoto.Deconverte(entidade.get_foto()));
}

} // namespace comum::asn
