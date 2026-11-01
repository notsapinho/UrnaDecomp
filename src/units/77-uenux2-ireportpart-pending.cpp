// Pending members: the Imprime of an api::IReportPart class of this unit. It is its class's key function, so the
// vtable is emitted here and needs it defined; this body is NOT the target's, it traps. With the vtable this object
// emits the class's implicit destructors, the compiler's code for the class definition (the fragment lists them); they
// move to the class's source with the vtable when Imprime does. Target function (vtable slot 2):
// - comum::CParteCandidatosConsultas::Imprime, fn 11212, record src/app/comum/relatorios/cpartecandidatos.cpp:174:19:
//   it waits for fn 4816, a std::sort instance over 32-bit words with its helpers (4809, 4810, 4813, 4814, 4815, 1506),
//   and for a CRespostas member binaryen inlined into it (a second stack frame that collects one post's record ids).
// CParteCandidatos::Imprime (fn 11215), CParteCandidatosMajoritarios::Imprime (fn 11214) and
// CParteCandidatosProporcionais::Imprime (fn 11213) are written in cpartecandidatos.cpp, and CParteEleitores::Imprime
// (fn 11206) in cparteeleitores.cpp.
#include "app/comum/relatorios/cpartecandidatos.h"

namespace comum {

void CParteCandidatosConsultas::Imprime() const
{
    __builtin_trap();
}

} // namespace comum
