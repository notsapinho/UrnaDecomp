#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CEmitirMaisBU (RTTI: si_class of comum::CAppState; vtable @1541172 [174, 144, 12082, 7480, 1661, 218, 425,
// 12081, 425]): it overrides StartState (slot 2) and ProcessInput (slot 7) and adds no data member, so the object is
// the base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144).
// final: fn 764 deletes the old object with no call through the vtable. A singleton: GetInst (fn 3879, a thunk into
// binaryen's fn 764) keeps the object in a static std::unique_ptr (@1833624, destroyed at exit by fn 12084) under a
// static std::mutex (@1833600, by fn 12083). The constructor passes 2 to the base's. StartState (fn 12082, records
// cemitirmaisbu.cpp 46 and 47) asserts that the vote is EAVENCERRADA and the closing EAEFIMDOSTRABALHOS, logs, and shows
// CTelasVota's +196; it is the class's key function, so cemitirmaisbu.cpp's object emits the vtable. ProcessInput (fn
// 12081) is pending in unit 104's file. src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and
// which is chosen.
class CEmitirMaisBU final : public comum::CAppState {
public:
    static CEmitirMaisBU& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEmitirMaisBU();

    static std::mutex s_mutex;
    static std::unique_ptr<CEmitirMaisBU> s_inst;
};

} // namespace vota
