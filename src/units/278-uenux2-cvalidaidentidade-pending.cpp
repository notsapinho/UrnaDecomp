// Pending members of vota::CValidaIdentidade (src/units/278-uenux2-cvalidaidentidade.mk), reached only through its
// vtable, which cvalidaidentidade.cpp emits with the destructor and which needs every slot defined. This body is NOT the
// target's, it traps. Move it into cvalidaidentidade.cpp when it is reconstructed, and delete this file with it.
//
// - vota::CValidaIdentidade::StartState (target fn 10627, slot 2, 3842 B): of its direct callees one has no name, 5420
//   (called twice; 10627 is its one caller), a std::map insertion (it calls __tree_balance_after_insert, fn 152, three
//   times; 1906, the map's tree destroy, which the destructor, fn 2749, calls too, matches), and it holds
//   vota::CIdentidadeInvalida's GetInst and constructor inlined (the one store of that vptr, 1588384) with its form. Not
//   written.
#include "app/vota/operador/leidentidade/cvalidaidentidade.h"

namespace vota {

void CValidaIdentidade::StartState()
{
    __builtin_trap();
}

} // namespace vota
