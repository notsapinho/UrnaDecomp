// Pending members: the two slots comum::asn::CConversorCabecalhoPacote's vtable needs, which no source of ours defines
// yet. A local of that class in ConvertePacotes and DesconvertePacotes (cconversorcabecalhopacote.cpp) stores its vptr,
// so its vtable must be in the link, and this object emits it.
// - DoConverte, slot 2, target fn 11438, and DoDesconverte, slot 3, fn 11437. They hold util.cpp's
//   DesconverteIdEleitoral, DesconverteTipoPacote and DesconverteIdSistema (records util.cpp:89, 329, 451) and
//   ConverteTipoPacote, ConverteIdPacote and ConverteIdSistema (231, 344, 419) inlined, and md::CIDEleitoral's,
//   CIDPacote's and CCabecalhoPacote's members (records cideleitoral.cpp:21, 29, 37, cidpacote.cpp:21, 67, 75, 83 and
//   ccabecalhopacote.cpp:33, 36, 39). None of those is written: they wait for those functions and members, util.cpp's
//   and the three classes', of which only the layouts are here (app/comum/md/ccabecalhopacote.h, cideleitoral.h).
//   Their stubs stay in app/comum/asn/util.cpp, where their inlined records put them: tools/round/stubs.py drops the
//   stub of a slot only for a vtable ledger/vtables.json lists (in_linked_vtable), and this class has no row there.
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"

namespace comum::asn {

ModuloTiposEleitorais::CabecalhoPacote CConversorCabecalhoPacote::DoConverte(const TDado&) const
{
    __builtin_trap();
}

md::CCabecalhoPacote CConversorCabecalhoPacote::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
