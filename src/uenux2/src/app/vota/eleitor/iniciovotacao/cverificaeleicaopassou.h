#pragma once

#include "app/comum/cappstate.h"

namespace vota {

// vota::CVerificaEleicaoPassou (RTTI: si_class of comum::CAppState; vtable @1544968 [174, 144, 11914, 7480, 1661, 218,
// 425, 218, 425]): it overrides StartState (slot 2, fn 11914, records cverificaeleicaopassou.cpp:56 and :70). Its one
// builder, fn 7160 (not written), holds its GetInst inlined: a 12-byte object, the base's size, so no data member, over
// the base's constructor with 0, kept in a static std::unique_ptr (@1834380) under a static std::mutex (@1834356), the
// old one deleted with no call through the vtable, so final; slots 0 and 1 hold the destructors the states with no
// member share (fns 174 and 144). GetInst and the statics are not written: they wait for fn 7160. StartState as the key
// function and this header's path, beside the .cpp its records name, are chosen.
class CVerificaEleicaoPassou final : public comum::CAppState {
public:
    virtual void StartState() override;
};

} // namespace vota
