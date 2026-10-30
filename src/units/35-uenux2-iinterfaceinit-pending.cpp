// Pending members: the comum::IInterfaceInit member src/uenux2/src/app/comum/iinterfaceinit.cpp does not hold yet. The
// class's vtable is emitted with the destructor, its key function, in that TU, and needs it defined; its body is NOT
// the target's, it traps. Target function: CurrentBootDevice 11646 (vtable slot 2), whose record puts a throw on line
// 47 col 15 of that file; it throws a CBaseError<comum::EUeComumError, {7200, 7600}> built by fn 480, which no
// evidence names yet.
// Move it into iinterfaceinit.cpp when it is reconstructed; delete this file with it.
#include "app/comum/iinterfaceinit.h"

namespace comum {

EBootDeviceId IInterfaceInit::CurrentBootDevice()
{
    __builtin_trap();
}

} // namespace comum
