// Pending members: the Imprime of each api::IReportPart class of this unit. Each is its class's key function, so the
// vtables are emitted here and need them defined; these bodies are NOT the target's, they trap. With each vtable this
// object emits the class's implicit destructors, the compiler's code for the class definitions (the fragment lists
// them); they move to each class's source with the vtable when Imprime does. Target functions (vtable slot 2):
// - comum::CParteCandidatosConsultas::Imprime, fn 11212, record src/app/comum/relatorios/cpartecandidatos.cpp:174:19:
//   it waits for fn 4816, a std::sort instance over 32-bit words with its helpers (4809, 4810, 4813, 4814, 4815, 1506),
//   and for a CRespostas member binaryen inlined into it (a second stack frame that collects one post's record ids).
// - CParteCandidatosProporcionais::Imprime, fn 11213: it waits for CCandidaturas::Localiza (record
//   ccandidaturas.cpp:56, inlined into it) and for CPartidos's records as an api::CDataMap<ueword, md::CPartido>, which
//   app/comum/dados/cpartidos.h does not declare yet; its throw's error constructor is fn 170.
// CParteCandidatos::Imprime (fn 11215) and CParteCandidatosMajoritarios::Imprime (fn 11214) are written in
// cpartecandidatos.cpp, and CParteEleitores::Imprime (fn 11206) in cparteeleitores.cpp.
// f11213's stub, in app/comum/dados/ccandidaturas.cpp (the file of a record its body holds), went with this trap.
#include "app/comum/relatorios/cpartecandidatos.h"

namespace comum {

void CParteCandidatosProporcionais::Imprime() const
{
    __builtin_trap();
}

void CParteCandidatosConsultas::Imprime() const
{
    __builtin_trap();
}

} // namespace comum
