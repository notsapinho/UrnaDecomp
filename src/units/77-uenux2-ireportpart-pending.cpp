// Pending members: the Imprime of each api::IReportPart class of this unit. Each is its class's key function, so the
// vtables are emitted here and need them defined; these bodies are NOT the target's, they trap. With each vtable this
// object emits the class's implicit destructors, the compiler's code for the class definitions (the fragment lists
// them); they move to each class's source with the vtable when Imprime does. Target functions (vtable slot 2):
// - comum::CParteCandidatos::Imprime, fn 11215; CParteCandidatosMajoritarios::Imprime, fn 11214, record
//   src/app/comum/relatorios/cpartecandidatos.cpp:75:19; CParteCandidatosConsultas::Imprime, fn 11212, record :174:19;
//   CParteCandidatosProporcionais::Imprime, fn 11213; CParteRdv::Imprime, fn 11203; CParteEleitores::Imprime, fn 11206.
//   They wait for callees no unit defines: fn 273 (comum::CCargos::GetInst by its record), fns 332, 2271,
//   2272, 2812, 4816, 2840, 1273, 1283, 3697, 326 and 5601, and their throws' error constructors 170 and 580.
// f11213's stub, in app/comum/dados/ccandidaturas.cpp (the file of a record its body holds), went with this trap.
#include "app/comum/relatorios/cpartecandidatos.h"
#include "app/comum/relatorios/cparteeleitores.h"
#include "app/comum/relatorios/cparterdv.h"

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

void CParteEleitores::Imprime() const
{
    __builtin_trap();
}

void CParteRdv::Imprime() const
{
    __builtin_trap();
}

} // namespace comum
