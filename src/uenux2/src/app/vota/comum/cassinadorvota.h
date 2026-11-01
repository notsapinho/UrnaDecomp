#pragma once

#include "app/comum/gravadores/cassinador.h"

namespace vota {

// vota::CAssinadorVota (RTTI: si_class of comum::CAssinador, typeinfo @1532320; vtable @1532304 [7766, 4694]). It adds
// no data member and overrides only the destructor, which is out of line: its D2 (fn 7766) is a function of its own, one
// call of the base's (fn 1007), and its D0 (fn 4694) calls the base's D2, drops the result and frees `this`, the base's
// D0 body, so one function fills both slots 1. Out of line `= default`, the link gives both; left implicit, it gives no
// D2 of the class's own and a D0 that frees what the base's D2 returns (measured: src/units/165-uenux2-app-vota-
// execucao.mk). So the destructor is the key function, and cassinadorvota.cpp emits the vtable. The constructor, fn 1501 (318 B, seven
// callers), is not reconstructed, so not declared: it inlines the base's and assigns two of its strings through fns
// 5462 and 2763, which have no name. No record names the class: the vtable and typeinfo lie in app/vota/comum/'s run of
// the data, before csincronizavota.cpp's first record, and the file, app/vota/comum/cassinadorvota.cpp, is the class's
// name in lower case, a choice.
class CAssinadorVota : public comum::CAssinador {
public:
    ~CAssinadorVota() override;
};

} // namespace vota
