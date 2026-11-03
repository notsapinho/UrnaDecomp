#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CEleitorEncontrado (RTTI: si_class of comum::CAppState; vtable @1588936 [174, 144, 10635, 7480, 1661, 218, 425,
// 218, 425]): the state that reads the voter found and goes to the state the voter's situation calls for. It overrides
// StartState (slot 2, fn 10635, record celeitorencontrado.cpp:102, which goes to one of ten states) and adds no data
// member, so the object is the base's 12 bytes, and
// slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final: the one function that
// creates it frees a replaced object with no call through the vtable. A singleton: fn 10631
// (vota::CProcuraEleitor::StartState) holds GetInst and the constructor inlined; GetInst keeps the object in a static
// std::unique_ptr (@1905616) under a static std::mutex (@1905592), and the constructor passes 0 to the base's.
// src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is chosen.
class CEleitorEncontrado final : public comum::CAppState {
public:
    static CEleitorEncontrado& GetInst();

    virtual void StartState() override;

private:
    CEleitorEncontrado();

    static std::unique_ptr<CEleitorEncontrado> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
