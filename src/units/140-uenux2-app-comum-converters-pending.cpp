// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet. Their
// bodies are NOT the target's; they trap.
// - CConversorEleicoesVota::DoDesconverte (slot 3, fn 11349, records cconversoreleicoesvota.cpp:69, :74, :94 and :104),
//   not written: it builds md::CVotosEleicoesVota's maps from the entity (5054 B); its direct callees 3869, 5640, 5643
//   and 5681 are not matched.
// - CConversorRegistroDigitalVoto<CConversorEleicoesVota>'s DoConverte and DoDesconverte (slots 2 and 3, fns 11483 and
//   11482), not written: the entity's header from the class's words and the elections through its member converter.
//   Explicit specializations of the class template's members for this instance; they move into the template when
//   written.
#include "app/comum/dados/asn/rdv/cconversoreleicoesvota.h"
#include "app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.h"

namespace comum::asn {

CConversorEleicoesVota::TDado CConversorEleicoesVota::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

template <>
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::TEntidade
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

template <>
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::TDado
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
