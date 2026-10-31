// Pending members: the two slots of comum::asn::CConversorHorarioVerao, whose vtable (@1569380) target fns 11383 and 11382
// need: both build the converter on the stack and call its slots through Converte and Desconverte. The vtable is emitted
// here, with the key function; the bodies are NOT the target's, they trap.
// - DoConverte, target fn 11385 (391 B), calls fn 3802 twice, which turns an api::CDate into the entity's date with the
//   format "YYYYMMDD" through fn 706, which has no name, and builds it with ASN1::AbstractString's constructor (fn 2190);
//   api::CDate has no such member here.
// - DoDesconverte, target fn 11384 (218 B), calls fn 2276 twice and compares through fn 1261; 2276 calls fns 2765 and 2201,
//   and 2765 is the api::CDate constructor unit 125 matches. It holds CHorarioVerao's constructor inlined, with the
//   record src/app/comum/dados/md/chorarioverao.cpp:29. That file held only 11384's stub, so it went with the stub.
// Move them into a cconversorhorarioverao.cpp when they are reconstructed; delete this file with them.
#include "app/comum/dados/asn/cconversorhorarioverao.h"

namespace comum::asn {

CConversorHorarioVerao::TEntidade CConversorHorarioVerao::DoConverte(const TDado&) const
{
    __builtin_trap();
}

CConversorHorarioVerao::TDado CConversorHorarioVerao::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
