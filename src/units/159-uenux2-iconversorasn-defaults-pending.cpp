// Pending members: the members the vtables of fragment 159's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap. Each is its class's only override and so its key function: this object
// emits the class's vtable, and with it the base's default the class inherits (iconversorasn.h's DoConverte or
// DoDesconverte, iconversorbiometriaasn.h's DoConverte), which is the header's code and matches from here.
// The stub of each member here went when this file landed; where it was the last stub of a stub-only file, that file
// went with it, and writing the member writes the file again at its records' lines (named below, under
// src/uenux2/src/app/comum/dados/).
// - comum::asn::CConversorCandidaturas::DoDesconverte (slot 3, fn 11445): it builds a comum::asn::CConversorCandidatura
//   on its stack (constructor fn 5712), whose entity type ModuloCandidatos::Candidatura the generated module lacks.
#include "app/comum/dados/asn/candidatura/cconversorcandidaturas.h"

namespace comum::asn {

CConversorCandidaturas::TDado CConversorCandidaturas::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
