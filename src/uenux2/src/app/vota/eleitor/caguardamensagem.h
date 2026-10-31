#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CAguardaMensagem (RTTI: si_class of comum::CAppState; vtable @1532956 [174, 144, 3243, 7480, 1661, 218, 7481,
// 218, 425]): it overrides StartState (slot 2) and ProcessKey (slot 6) and adds no data member, so the object is the
// base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final: fn
// 764 deletes the old object with no call through the vtable. A singleton: GetInst (fn 1337, a thunk into binaryen's
// fn 764) keeps the object in a static std::unique_ptr (@1832964, destroyed at exit by fn 7485) under a static
// std::mutex (@1832940, by fn 7482). The constructor passes 1 to the base's. src/units/104-uenux2-app-vota-estados.mk
// says which of this is evidence and which is chosen.
class CAguardaMensagem final : public comum::CAppState {
public:
    static CAguardaMensagem& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

private:
    CAguardaMensagem();

    static std::mutex s_mutex;
    static std::unique_ptr<CAguardaMensagem> s_inst;
};

} // namespace vota
