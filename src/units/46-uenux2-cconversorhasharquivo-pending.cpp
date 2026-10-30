// Pending members: the CConversorHashArquivo member src/uenux2/src/app/comum/gravadores/asn/cconversorhasharquivo.cpp
// does not hold yet. The class's vtable (emitted with DoConverte in that TU) needs it defined; its body is NOT the
// target's, it traps. Target function: DoDesconverte 10269 (vtable slot 3), which copies the entity's nomeArquivo and
// assinatura into two strings and builds the api::hash::CHashArquivo from them through its constructor (fn 3600, no
// name yet; it lives in api/hash/chasharquivo.cpp with ValidaObjeto, fn 5364, which calls the unnamed fn 2723).
// Move it into cconversorhasharquivo.cpp when it is reconstructed; delete this file with it.
#include "app/comum/gravadores/asn/cconversorhasharquivo.h"

namespace comum::asn {

CConversorHashArquivo::TDado CConversorHashArquivo::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
