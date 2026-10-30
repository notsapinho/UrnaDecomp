// Pending members: the CVisitanteFoto member src/uenux2/src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp does not
// hold yet. The class's vtable (emitted with the destructor, its key function, in that TU) needs it defined; its body is
// NOT the target's, it traps. Target function: visit 11442 (vtable slot 2, 1198 B), whose records put its four throws
// on lines 40, 48, 56 (col 19) and 63 (col 15) of that file. It waits for src/asn1/asn1.h to declare the base's slot as
// the records spell it (ASN1::IAbstractVisitor::EVisitorResult visit(int, const std::string &, ASN1::AbstractData &,
// size_t, size_t)); the signature below is asn1.h's.
// Move it into cvisitantefoto.cpp when it is reconstructed; delete this file with it.
#include "app/comum/dados/asn/candidatura/cvisitantefoto.h"

namespace comum::asn {

int CVisitanteFoto::visit(int, const std::string&, ASN1::AbstractData*, unsigned, unsigned)
{
    __builtin_trap();
}

} // namespace comum::asn
