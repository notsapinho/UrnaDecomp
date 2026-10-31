// Pending members: the comum::CGravadorRCSecao member src/uenux2/src/app/comum/gravadores/cgravadorrcsecao.cpp does
// not hold yet. Its body is NOT the target's, it traps. GravaResultado, fn 11616 (slot 7, 15849 B, record
// cgravadorrcsecao.cpp:110), is the class's first out-of-line virtual member, so its vtable (@1554740) is emitted here,
// and with it the implicit deleting destructor of slot 1 (fn 11615), the compiler's code for the class definition in
// cgravadorrcsecao.h; slot 0 holds IResultado's base-object destructor (fn 12090). GravaResultado calls
// CriaIdentidadeEleitor (fn 5845) and many functions not written yet; it goes in cgravadorrcsecao.cpp when it is
// reconstructed, and the vtable and the deleting destructor move there with it, under the same symbols. Delete this file
// with it.
#include "app/comum/gravadores/cgravadorrcsecao.h"

namespace comum {

void CGravadorRCSecao::GravaResultado(api::CFile&) const
{
    __builtin_trap();
}

} // namespace comum
