// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet. Their
// bodies are NOT the target's; they trap.
// - CConversorEleicoesVota::DoDesconverte (slot 3, fn 11349, records cconversoreleicoesvota.cpp:69, :74, :94 and :104),
//   not written: it builds md::CVotosEleicoesVota's maps from the entity (5054 B); of its direct callees, 3869 and 5681
//   have no body of ours, and md::CVotosCargos' and md::CVotosEleicoesVota's constructors (5643, 5640) match.
// - CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoConverte (slot 2, fn 11483), an explicit specialization of
//   the class template's member for this instance, which moves into the template when written. What it waits for: the
//   form of its historicoCodigosCarga loop. The target holds that loop in a function binaryen inlined (a second frame of
//   48 bytes, and a two-word result, the end of m_historicoCodigosCarga and the list's address, stored back into the
//   caller's frame), which per string copies the std::string, builds an ASN1::GeneralString from the copy, calls
//   AbstractString::do_clone (fn 3481) directly and the container's push_back (fn 543) out of line. Measured on this
//   object, the rest written as the target's order shows (municipioZona, identificacao, the member converter's
//   Converte, then the entity's five fields): std::copy into a back_inserter gives 253 rows over 588,
//   std::ranges::transform with a by-value std::string lambda 279 over 625, std::ranges::for_each pushing a
//   GeneralString 273 over 620; in each, clang inlines the loop, push_back and the vector's growth and calls clone
//   through the vtable. The target also builds a Constrained_INTEGER temporary for pleito, which
//   ModuloRegistroDigitalVoto.h's int_type setter does not give: that setter takes const_reference when this lands.
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

} // namespace comum::asn
