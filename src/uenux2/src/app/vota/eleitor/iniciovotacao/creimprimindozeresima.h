#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CReimprimindoZeresima (RTTI: si_class of comum::CAppState; vtable @1546268 [174, 144, 11852, 7480, 1661, 218,
// 425, 218, 425]): it overrides StartState (slot 2) and adds no data member, so the object is the base's 12 bytes, and
// slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final: fn 764 deletes the old
// object with no call through the vtable. A singleton: GetInst (fn 5941, a thunk into binaryen's fn 764) keeps the
// object in a static std::unique_ptr (@1834828, destroyed at exit by fn 11854) under a static std::mutex (@1834804, by
// fn 11853). The constructor passes 0 to the base's. src/units/104-uenux2-app-vota-estados.mk says which of this is
// evidence and which is chosen. StartState (fn 11852) holds ImprimeZeresima, the record's name
// (creimprimindozeresima.cpp:51, `void vota::CReimprimindoZeresima::ImprimeZeresima()`, no `static` and no `virtual`),
// after a stack prologue of its own: out of line, and inlined by binaryen into its one caller; its access is chosen.
class CReimprimindoZeresima final : public comum::CAppState {
public:
    static CReimprimindoZeresima& GetInst();

    virtual void StartState() override;

private:
    CReimprimindoZeresima();

    void ImprimeZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CReimprimindoZeresima> s_inst;
};

} // namespace vota
