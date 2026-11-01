// Pending members: the members the vtables of fragment 159's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap. Each is its class's only override and so its key function: this object
// emits the class's vtable, and with it the base's default the class inherits (iconversorasn.h's DoConverte or
// DoDesconverte, iconversorbiometriaasn.h's DoConverte), which is the header's code and matches from here.
// The stub of each member here went when this file landed; where it was the last stub of a stub-only file, that file
// went with it, and writing the member writes the file again at its records' lines (named below, under
// src/uenux2/src/app/comum/dados/).
// - comum::asn::CConversorDetalheCandidato::DoDesconverte (slot 3, fn 11375, records
//   asn/processoeleitoral/cconversordetalhecandidato.cpp:29, :34 and :39; that stub-only file went), not written: fn
//   1135 has no name (2341 matches since fragment 191).
// - comum::asn::CConversorDetalheConsulta::DoDesconverte (slot 3, fn 11377: md::CDetalheConsulta's and
//   md::CRespostaConsulta's constructors inlined, records md/processoeleitoral/cdetalheconsulta.cpp:29 and :32, a
//   stub-only file that went, and crespostaconsulta.cpp:29 and :32), not written; its callees have names (1880 since
//   unit 00, 3018 since fragment 191).
// - comum::asn::CConversorEleicaoPE::DoDesconverte (slot 3, fn 11371: md::CEleicaoPE's checks inlined, records
//   md/processoeleitoral/celeicaope.cpp:63 to :92), not written: fns 2289 and 3816 have no name.
// - comum::asn::CConversorDedo::DoDesconverte (slot 3, fn 11416, records asn/eleitor/cconversordedo.cpp:159 and :169, a
//   stub-only file that went, and md/eleitor/cdedo.cpp:28 and :33), not written: fn 5702 has no name.
// - comum::asn::CConversorBiometriaEleitor::DoDesconverte (slot 3, fn 11422, record
//   asn/eleitor/cconversorbiometriaeleitor.cpp:26, a stub-only file that went), not written: fn 781 has no name (2799
//   matches since md/ builds with strict aliasing, and 5708, which it calls too, from unit 166's tree root).
// - comum::asn::CConversorBiometriaEleitorCifrada::DoDesconverte (slot 3, fn 11419, records of its inlined LeChave at
//   asn/eleitor/cconversorbiometriaeleitorcifrada.cpp:91, :101 and :109), not written: fns 183, 518, 679 and others
//   have no name (412 has one since, unit 32's).
// - comum::asn::CConversorEntidadeHashes::DoConverte (slot 2, fn 10266, 1338 B), not written: md::CEntidadeHashes's
//   members past +36 are not recovered (unit 160's fragment).
// - comum::asn::CConversorCandidaturas::DoDesconverte (slot 3, fn 11445): it builds a comum::asn::CConversorCandidatura
//   on its stack (constructor fn 5712), whose entity type ModuloCandidatos::Candidatura the generated module lacks.
#include "app/comum/dados/asn/candidatura/cconversorcandidaturas.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitorcifrada.h"
#include "app/comum/dados/asn/eleitor/cconversordedo.h"
#include "app/comum/dados/asn/processoeleitoral/cconversordetalhecandidato.h"
#include "app/comum/dados/asn/processoeleitoral/cconversordetalheconsulta.h"
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"
#include "app/comum/gravadores/asn/cconversorentidadehashes.h"

namespace comum::asn {

md::CDetalheCandidato CConversorDetalheCandidato::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

CConversorDetalheConsulta::TDado CConversorDetalheConsulta::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

CConversorEleicaoPE::TDado CConversorEleicaoPE::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

md::CDedo CConversorDedo::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

md::CBiometriaEleitor CConversorBiometriaEleitor::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

CConversorBiometriaEleitorCifrada::TDado CConversorBiometriaEleitorCifrada::DoDesconverte(
    const TEntidade&, const md::CParametro&) const
{
    __builtin_trap();
}

CConversorCandidaturas::TDado CConversorCandidaturas::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

CConversorEntidadeHashes::TEntidade CConversorEntidadeHashes::DoConverte(const TDado&) const
{
    __builtin_trap();
}

} // namespace comum::asn
