// Pending members: the comum::CSigVerifier member src/uenux2/src/app/comum/relatorios/csigverifier.cpp does not hold
// yet. The class's vtable is emitted with Verify, its key function (the destructor is implicit), and needs it defined;
// its body is NOT the target's, it traps. Target function: Verify 11179 (vtable slot 2), whose record puts the
// CPolySingleton<IInterfaceSavd>::instance() call on line 32 col 19 of that file; it inlines comum::ValidarUE
// (iinterfacesavd.cpp:898) and calls 5892, 1822, 178 and 183, none of them named yet.
// Move it into csigverifier.cpp when it is reconstructed; delete this file with it.
#include "app/comum/relatorios/csigverifier.h"

namespace comum {

void CSigVerifier::Verify() const
{
    __builtin_trap();
}

} // namespace comum
