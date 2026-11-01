#pragma once

#include "app/comum/cappstate.h"

namespace vota {

// vota::CVerificaQtdBUsAdicionais (RTTI: si_class of comum::CAppState; vtable @1542916 [174, 144, 12023, 7480, 1661,
// 218, 425, 218, 425]): it overrides StartState (slot 2, fn 12023, records lines 36 and 37), which asserts that the
// vote is EAVENCERRADA and its closing EAEFIMDOSTRABALHOS and goes to CLimiteCopiasBUAtingido when GetNumViasBU() plus
// GetNumViasBUAdicionais() of the election's information is at most GetQtdBU(), else to CEmitirMaisBU. It adds no data
// member, so slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final: its GetInst,
// inlined into fn 7160, frees the old object with no call through the vtable. That GetInst (the object in a static
// std::unique_ptr @1833988 under a static std::mutex @1833964, the base's constructor called with 0) is not
// reconstructed: its one caller, fn 7160, is not written. This header's path is chosen, beside the .cpp the records
// name.
class CVerificaQtdBUsAdicionais final : public comum::CAppState {
public:
    virtual void StartState() override;
};

} // namespace vota
