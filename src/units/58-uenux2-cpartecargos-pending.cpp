// Pending members: the comum::CParteCargos member src/uenux2/src/app/comum/relatorios/cpartecargos.cpp does not hold
// yet. The class's vtable is emitted with Imprime, its key function (the destructor is implicit), and needs it
// defined; its body is NOT the target's, it traps. With the vtable this object also emits the implicit destructors
// (target fns 11208 and 11207, vtable slots 0 and 1), the compiler's code for the class definition in
// cpartecargos.h; they move to cpartecargos.cpp.o with the vtable when Imprime does.
// Target function: Imprime 11209 (vtable slot 2, vtable @1576556; ledger/vtables.json). It calls
// comum::CCargos::GetInst (fn 273), GetCurrentEleicaoID (fn 2835) and Next (fn 1708), which their records name and
// no unit defines yet, the end test fn 602 (no record), and fn 2269, CCargos's reset of its index, a binaryen twin
// already matched as pthread_mutexattr_init.
// Move it into cpartecargos.cpp when it is reconstructed; delete this file with it.
#include "app/comum/relatorios/cpartecargos.h"

namespace comum {

void CParteCargos::Imprime() const
{
    __builtin_trap();
}

} // namespace comum
