#pragma once

#include "asn1/asn1.h"

namespace comum::asn {

// RTTI: an si_class of ASN1::IAbstractVisitor, vtable [5698, 11408, 11407]; the path is the record's
// (cvisitanteeleitor.cpp:91, visit). Recovered: the head only. fn 11523 builds it as a
// std::shared_ptr<CVisitanteEleitor>(new CVisitanteEleitor), and the block's __on_zero_shared is the shared call
// through the vtable (fn 172), so the class is not final. The members, the constructor and visit are not reconstructed.
class CVisitanteEleitor : public ASN1::IAbstractVisitor {};

} // namespace comum::asn
