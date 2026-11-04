#pragma once

#include "app/comum/cappstate.h"

// vota::IAjusteInicial, the state the voter's thread starts its machine in. RTTI gives the class, a si_class of
// comum::CAppState (typeinfo @1534436), and its one implementer, vota::CAjusteInicial (cajusteinicial.h). Its GetInst
// is the record cajusteinicial.cpp:57 (static IAjusteInicial &vota::IAjusteInicial::GetInst()), which binaryen inlined
// into its one caller, vota::CThreadEleitor::Run (fn 7061): the poly singleton's instance, CAjusteInicial set as the
// default when none is registered. It adds no virtual member: CAjusteInicial's vtable is CAppState's with slot 2 its
// own, and the target has no vtable of this class. The path, beside cajusteinicial.cpp, is chosen; src/units/
// 329-uenux2-cajusteinicial.mk says what else is.

namespace vota {

class IAjusteInicial : public comum::CAppState {
public:
    static IAjusteInicial& GetInst();
};

} // namespace vota
