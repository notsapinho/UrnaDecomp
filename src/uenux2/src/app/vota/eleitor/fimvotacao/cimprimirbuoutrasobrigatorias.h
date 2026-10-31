#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CImprimirBUOutrasObrigatorias (RTTI: si_class of comum::CAppState; vtable @1541740 [174, 144, 12065, 7480,
// 1661, 218, 425, 218, 425]): it overrides StartState (slot 2) and adds no data member, so the object is the base's 12
// bytes, and slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final: fn 764
// deletes the old object with no call through the vtable. A singleton: GetInst (fn 5984, a thunk into binaryen's fn
// 764) keeps the object in a static std::unique_ptr (@1833764, destroyed at exit by fn 12067) under a static
// std::mutex (@1833740, by fn 12066). The constructor passes 0 to the base's. src/units/104-uenux2-app-vota-estados.mk
// says which of this is evidence and which is chosen.
class CImprimirBUOutrasObrigatorias final : public comum::CAppState {
public:
    static CImprimirBUOutrasObrigatorias& GetInst();

    virtual void StartState() override;

private:
    CImprimirBUOutrasObrigatorias();

    static std::mutex s_mutex;
    static std::unique_ptr<CImprimirBUOutrasObrigatorias> s_inst;
};

} // namespace vota
