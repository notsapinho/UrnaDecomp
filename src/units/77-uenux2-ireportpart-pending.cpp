// Pending members: the Imprime of each api::IReportPart class of this unit. Each is its class's key function, so the
// vtables are emitted here and need them defined; these bodies are NOT the target's, they trap. With each vtable this
// object emits the class's implicit destructors, the compiler's code for the class definitions (the fragment lists
// them); they move to each class's source with the vtable when Imprime does. Target functions (vtable slot 2):
// - comum::CParteCandidatos::Imprime, fn 11215; CParteCandidatosMajoritarios::Imprime, fn 11214, record
//   src/app/comum/relatorios/cpartecandidatos.cpp:75:19; CParteCandidatosConsultas::Imprime, fn 11212, record :174:19;
//   CParteCandidatosProporcionais::Imprime, fn 11213. They wait for callees no unit defines: fns 2271, 2272, 4816, 2840
//   and 1273, and their throws' error constructor 170 (580, the other, matches since unit 123). CParteEleitores::Imprime
//   (fn 11206) is written, in cparteeleitores.cpp, which now emits that class's vtable and destructors.
// f11213's stub, in app/comum/dados/ccandidaturas.cpp (the file of a record its body holds), went with this trap.
#include "app/comum/relatorios/cpartecandidatos.h"

namespace comum {

void CParteCandidatos::Imprime() const
{
    __builtin_trap();
}

void CParteCandidatosMajoritarios::Imprime() const
{
    __builtin_trap();
}

void CParteCandidatosProporcionais::Imprime() const
{
    __builtin_trap();
}

void CParteCandidatosConsultas::Imprime() const
{
    __builtin_trap();
}

} // namespace comum
