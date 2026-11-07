// Pending member of unit 440 (src/units/440-uenux2-votainit.mk), a trap until it is reconstructed (src/units/README.md
// "Pending members"):
// - vota::CTelasVota::CreateInst (target fn 7787, record ctelasvota.cpp:3435, 148,912 B with the constructor, record
//   :3502, and about 148 one-caller bodies inlined), which votaInit (fn 7840, unit 170's TU) invokes through table slot
//   39. It holds that call's place: votaInit's call needs a definition our link has. It is not written; it moves into
//   src/uenux2/src/app/vota/eleitor/comum/ctelasvota.cpp with its body, and this file and its rule go with it.
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

void CTelasVota::CreateInst()
{
    __builtin_trap();
}

} // namespace vota
