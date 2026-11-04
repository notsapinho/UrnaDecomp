#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CFinalizaAquisicao (RTTI: si_class of comum::CAppState; vtable @1540308 [174, 144, 12113, 7480, 1661, 218, 425,
// 218, 425]): it overrides StartState (slot 2) and adds no data member, so the object is the base's 12 bytes, and slots
// 0 and 1 hold the destructors the states with no member share (fns 174 and 144). A singleton of unit 104's shape: fn
// 7160 (vota::CAjusteInicial, records cajusteinicial.cpp) holds GetInst inlined, which keeps the object in a static
// std::unique_ptr (@1833468, destroyed at exit by fn 12115) under a static std::mutex (@1833444, by fn 12114), allocates
// 12 bytes, passes 0 to the base's constructor, stores the vptr and frees the old object with no call through the
// vtable (final). src/units/223-uenux2-cfinalizaaquisicao.mk says which of this is evidence and which is chosen.
class CFinalizaAquisicao final : public comum::CAppState {
public:
    static CFinalizaAquisicao& GetInst();

    virtual void StartState() override;

private:
    CFinalizaAquisicao();

    static std::mutex s_mutex;
    static std::unique_ptr<CFinalizaAquisicao> s_inst;
};

} // namespace vota
