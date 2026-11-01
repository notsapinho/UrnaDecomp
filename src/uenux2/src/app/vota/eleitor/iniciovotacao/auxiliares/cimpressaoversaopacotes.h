#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CImpressaoVersaoPacotes (RTTI: si_class of comum::CAppState; vtable @1545168 [174, 144, 11905, 7480, 1661, 218,
// 425, 218, 425]): the state vota::CMaisInformacoes::ProcessInput (fn 11896) goes to for option 3. It overrides
// StartState (slot 2, fn 11905, 5098 B, pending:
// src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp) and adds no data member, so the object is
// the base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final:
// GetInst deletes the old object with no call through the vtable. A singleton: GetInst, held inlined by fn 11896, keeps
// the object in a static std::unique_ptr (@1834464, destroyed at exit by fn 11907) under a static std::mutex (@1834440,
// by fn 11906). The constructor passes 2 to the base's. src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk
// says which of this is evidence and which is chosen.
class CImpressaoVersaoPacotes final : public comum::CAppState {
public:
    static CImpressaoVersaoPacotes& GetInst();

    virtual void StartState() override;

private:
    CImpressaoVersaoPacotes();

    static std::mutex s_mutex;
    static std::unique_ptr<CImpressaoVersaoPacotes> s_inst;
};

} // namespace vota
