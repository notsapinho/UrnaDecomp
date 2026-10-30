// Pending members: the CConversorPartido member src/uenux2/src/app/comum/dados/asn/cconversorpartido.cpp does not hold
// yet. The class's vtable (emitted with DoConverte in that TU) needs it defined; its body is NOT the target's, it
// traps. Target function: DoDesconverte 11459 (vtable slot 3), which builds a comum::md::CPartido with its
// constructor and ValidaCriacao inlined (records md/cpartido.cpp:30, 33, 36) and throws through the CBaseError
// constructor fn 170, which nothing names yet.
// Move it into cconversorpartido.cpp when it is reconstructed; delete this file with it.
#include "app/comum/dados/asn/cconversorpartido.h"

namespace comum::asn {

CConversorPartido::TDado CConversorPartido::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
