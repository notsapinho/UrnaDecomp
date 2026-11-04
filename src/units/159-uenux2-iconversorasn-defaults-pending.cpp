// Pending members: the members the vtables of fragment 159's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap. Each is its class's only override and so its key function: this object
// emits the class's vtable, and with it the base's default the class inherits (iconversorasn.h's DoConverte or
// DoDesconverte, iconversorbiometriaasn.h's DoConverte), which is the header's code and matches from here.
// The stub of each member here went when this file landed; where it was the last stub of a stub-only file, that file
// went with it, and writing the member writes the file again at its records' lines (named below, under
// src/uenux2/src/app/comum/dados/).
// - comum::asn::CConversorEntidadeHashes::DoConverte (slot 2, fn 10266, 1338 B), not written: md::CEntidadeHashes's
//   members past +36 are not recovered (unit 160's fragment).
// - comum::asn::CConversorCandidaturas::DoDesconverte (slot 3, fn 11445): it builds a comum::asn::CConversorCandidatura
//   on its stack (constructor fn 5712), whose entity type ModuloCandidatos::Candidatura the generated module lacks.
// - comum::asn::CConversorEntidadeBU::DoConverte (slot 2, fn 10273, 12196 B, records
//   gravadores/asn/cconversorentidadebu.cpp:87 to :299, a stub-only file that went with its stub), not written: it
//   builds the whole BU entity from md::CEntidadeBU, whose members from +160 on are not recovered (centidadebu.h), with
//   CConversorEntidadeBU's static ConverteTipoVoto and ConverteTipoCargo, the file's anonymous Cria* helpers and
//   comum::asn::CAssinaVotavelBu::Assinar (record gravadores/asn/cassinavotavelbu.cpp:89) inlined, and calls fn
//   3603, the GetInst of an empty singleton with its statics at 1909976 and 1910000, which nothing else calls.
#include "app/comum/dados/asn/candidatura/cconversorcandidaturas.h"
#include "app/comum/gravadores/asn/cconversorentidadebu.h"
#include "app/comum/gravadores/asn/cconversorentidadehashes.h"

namespace comum::asn {

CConversorCandidaturas::TDado CConversorCandidaturas::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

CConversorEntidadeHashes::TEntidade CConversorEntidadeHashes::DoConverte(const TDado&) const
{
    __builtin_trap();
}

CConversorEntidadeBU::TEntidade CConversorEntidadeBU::DoConverte(const TDado&) const
{
    __builtin_trap();
}

} // namespace comum::asn
