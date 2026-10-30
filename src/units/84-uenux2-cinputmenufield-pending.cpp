// Pending members: the api::CMenuValidation member src/uenux2/src/api/gui/cinputmenufield.cpp does not hold yet. isValid
// is the class's key function, so this object emits the vtable; the body below is NOT the target's, it traps. Target
// function:
//   10900 isValid(const std::string&) const: calls fn 925 (CPolySingleton<IBeep>'s instance), which has no name yet, twice:
//         records cinputmenufield.cpp:198:5 and :210:5, matchesExactly and matchesPartially, which binaryen inlined
// Move it into cinputmenufield.cpp when it is reconstructed; delete this file with it.
#include "api/gui/cinputmenufield.h"

namespace api {

bool CMenuValidation::isValid(const std::string&) const
{
    __builtin_trap();
}

} // namespace api
