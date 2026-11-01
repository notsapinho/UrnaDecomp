// Pending members: the comum::CGravadorBU member no source of ours holds yet. Its body is NOT the target's, it traps.
// GravaResultado, fn 11629 (slot 7, 15903 B, records cgravadorbu.cpp:484 and :485, with those of LeChavePublica and
// MontaEntidadeBU, lines 542 to 636, inlined into it), is the class's first out-of-line virtual member, so its vtable
// (@1554132) is emitted here, and with it the implicit destructors of slots 0 and 1 (fns 5857, 11628), the compiler's
// code for the class definition in app/comum/gravadores/cgravadorbu.h. GravaResultado calls fns 3819 (which calls
// AcrescentaVotoVotavel, fn 3820, record cgravadorbu.cpp:221) and 2853 and many functions not written yet; it goes in
// cgravadorbu.cpp when it is reconstructed, and the vtable and the destructors move there with it, under the same
// symbols. Delete this file with it. cgravadorbu.cpp is a stub-only file until then: its record lines 221, 484, 485,
// 542, 552, 560 and 636 belong to functions not written.
#include "app/comum/gravadores/cgravadorbu.h"

namespace comum {

void CGravadorBU::GravaResultado(api::CFile&) const
{
    __builtin_trap();
}

} // namespace comum
