#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CIniciaFinalizacao (RTTI: si_class of comum::CAppState; vtable @1587868 [174, 144, 10706, 7480, 1661, 218, 425,
// 218, 425]): the first step of closing the voting. It overrides StartState (slot 2, fn 10706) and adds no data member:
// the object is the base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share (fns 174
// and 144), the implicit destructor's. StartState is the key function. A singleton: GetInst creates the object under
// a static std::mutex (@1905228) and keeps it in a static std::unique_ptr (@1905252), the constructor passing
// EVENTO_NENHUM (0) to the base's; binaryen inlines GetInst into its one caller, vota::CEscolheOpcao::ProcessInput (fn
// 10689, pending), so GetInst, the constructor and the statics are declared and not written here: they wait for that
// caller. src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CIniciaFinalizacao final : public comum::CAppState {
public:
    static CIniciaFinalizacao& GetInst();

    virtual void StartState() override;

private:
    CIniciaFinalizacao();

    static std::unique_ptr<CIniciaFinalizacao> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
