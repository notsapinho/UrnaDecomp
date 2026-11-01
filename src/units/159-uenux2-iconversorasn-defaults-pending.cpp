// Pending members: the members the vtables of fragment 159's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap. Each is its class's only override and so its key function: this object
// emits the class's vtable, and with it the base's default the class inherits (iconversorasn.h's DoConverte or
// DoDesconverte, iconversorbiometriaasn.h's DoConverte), which is the header's code and matches from here.
// The stub of each member here went when this file landed; where it was the last stub of a stub-only file, that file
// went with it, and writing the member writes the file again at its records' lines (named below, under
// src/uenux2/src/app/comum/dados/).
// - comum::asn::CConversorHistoricoVotoImpresso::DoConverte (slot 2, target fn 10276): it builds the entity's
//   dataHoraLigamento through fn 1080 (which stores ModuloTiposEleitorais::DataHoraJE's vptr), which has no name.
// - comum::asn::CConversorCargo::DoDesconverte (slot 3, fn 11373, records asn/processoeleitoral/cconversorcargo.cpp:69
//   and :83, the second DesconverteTipoCargo inlined; that stub-only file went), not written: fns 365 and 3018 have no
//   name.
// - comum::asn::CConversorDetalheCandidato::DoDesconverte (slot 3, fn 11375, records
//   asn/processoeleitoral/cconversordetalhecandidato.cpp:29, :34 and :39; that stub-only file went), not written: fns
//   1135 and 2341 have no name.
// - comum::asn::CConversorDetalheConsulta::DoDesconverte (slot 3, fn 11377: md::CDetalheConsulta's and
//   md::CRespostaConsulta's constructors inlined, records md/processoeleitoral/cdetalheconsulta.cpp:29 and :32, a
//   stub-only file that went, and crespostaconsulta.cpp:29 and :32), not written: fns 1880 and 3018 have no name.
// - comum::asn::CConversorEleicaoPE::DoDesconverte (slot 3, fn 11371: md::CEleicaoPE's checks inlined, records
//   md/processoeleitoral/celeicaope.cpp:63 to :92), not written: fns 2289, 3714 and 3816 have no name.
// - comum::asn::CConversorDedo::DoDesconverte (slot 3, fn 11416, records asn/eleitor/cconversordedo.cpp:159 and :169, a
//   stub-only file that went, and md/eleitor/cdedo.cpp:28 and :33), not written: fn 5702 has no name.
// - comum::asn::CConversorBiometriaEleitor::DoDesconverte (slot 3, fn 11422, record
//   asn/eleitor/cconversorbiometriaeleitor.cpp:26, a stub-only file that went), not written: fns 781, 2799 and 5708
//   have no name.
// - comum::asn::CConversorBiometriaEleitorCifrada::DoDesconverte (slot 3, fn 11419, records of its inlined LeChave at
//   asn/eleitor/cconversorbiometriaeleitorcifrada.cpp:91, :101 and :109), not written: fns 183, 412, 518, 679 and
//   others have no name.
// - comum::asn::CConversorCandidaturas::DoDesconverte (slot 3, fn 11445): it builds a comum::asn::CConversorCandidatura
//   on its stack (constructor fn 5712), whose entity type ModuloCandidatos::Candidatura the generated module lacks.
// - comum::asn::CConversorFotoCandidato::DoDesconverte (slot 3, fn 11440): it converts the photo through fn 5708, the
//   Desconverte of ecourna's CConversorFoto, which has no body of ours.
#include "app/comum/dados/asn/candidatura/cconversorcandidaturas.h"
#include "app/comum/dados/asn/candidatura/cconversorfotocandidato.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitorcifrada.h"
#include "app/comum/dados/asn/eleitor/cconversordedo.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorcargo.h"
#include "app/comum/dados/asn/processoeleitoral/cconversordetalhecandidato.h"
#include "app/comum/dados/asn/processoeleitoral/cconversordetalheconsulta.h"
#include "app/comum/dados/asn/processoeleitoral/cconversoreleicaope.h"
#include "app/comum/gravadores/asn/cconversorhistoricovotoimpresso.h"

namespace comum::asn {

CConversorHistoricoVotoImpresso::TEntidade CConversorHistoricoVotoImpresso::DoConverte(const TDado&) const
{
    __builtin_trap();
}

md::CCargo CConversorCargo::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

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

CConversorFotoCandidato::TDado CConversorFotoCandidato::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
