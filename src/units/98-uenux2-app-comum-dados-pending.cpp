// Pending member: the member comum::asn::CConversorImpedido's vtable needs and no source of ours defines yet. Its body is
// NOT the target's; it traps. DoDesconverte (slot 3, target fn 11410, record cconversorimpedido.cpp:40 of its inlined
// MontaEleitorIdentidade) waits for fn 566. It is the class's only override and so its key function:
// this object emits the vtable, and with it the base's default DoConverte (slot 2, fn 11409), iconversorasn.h's code,
// which matches from here.
#include "app/comum/dados/asn/eleitor/cconversorimpedido.h"
#include "app/comum/dados/md/eleitor/cimpedido.h"

namespace comum::asn {

CConversorImpedido::TDado CConversorImpedido::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
