#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CVerificaEleicaoPassou (RTTI: si_class of comum::CAppState; vtable @1544968 [174, 144, 11914, 7480, 1661, 218,
// 425, 218, 425]): it overrides StartState (slot 2, fn 11914, records cverificaeleicaopassou.cpp:56 and :70). Its one
// builder, vota::CAjusteInicial::StartState (fn 7160), holds its GetInst inlined by binaryen: a 12-byte object, the
// base's size, so no data member, over the base's constructor with 0, kept in a static std::unique_ptr (@1834380,
// destroyed at exit by fn 11916) under a static std::mutex (@1834356, by fn 11915), the old one deleted with no call
// through the vtable, so final; slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144).
// StartState as the key function, unit 104's names for GetInst and the statics and this header's path, beside the .cpp
// its records name, are chosen.
class CVerificaEleicaoPassou final : public comum::CAppState {
public:
    static CVerificaEleicaoPassou& GetInst();

    virtual void StartState() override;

private:
    CVerificaEleicaoPassou();

    static std::mutex s_mutex;
    static std::unique_ptr<CVerificaEleicaoPassou> s_inst;
};

} // namespace vota
