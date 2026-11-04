#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CImprimirBJust (RTTI: si_class of comum::CAppState; vtable @1541636 [174, 144, 12068, 7480, 1661, 218, 425, 218,
// 425]): it overrides StartState (slot 2, fn 12068, records cimprimirbjust.cpp 51 and 52) and adds no data member, so
// the object is the base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share (fns 174
// and 144). StartState asserts the vote's and the closing's states, logs the report (CLogVota::LogaImprimindoRelatorio,
// fn 1127, with RELATORIO_BUJ and 1), prints the justification report (imprimeBJust, record cimprimirbjust.cpp:69,
// `void vota::CImprimirBJust::imprimeBJust()`, out of line in the object: fn 12068 holds it behind a second
// stack-pointer prologue) and goes to vota::CImprimindoBim when comum::CInformacaoEleicao::ImprimeBJust (fn 1950) holds,
// else to vota::CRetirarMR. A singleton: GetInst, inlined into vota::CImprimirBUOutrasObrigatorias::StartState (fn
// 12065), keeps the object in a static std::unique_ptr (@1833736, destroyed at exit by fn 12070) under a static
// std::mutex (@1833712, by fn 12069), and builds it as the base's constructor with 0 and the vptr 1541644,
// vota::CImprimindoBim's shape (src/units/104-uenux2-app-vota-estados.mk). Chosen: the names GetInst, s_inst and
// s_mutex, imprimeBJust's being private, and this header's path, beside the .cpp the records name.
class CImprimirBJust final : public comum::CAppState {
public:
    static CImprimirBJust& GetInst();

    virtual void StartState() override;

private:
    CImprimirBJust();

    void imprimeBJust();

    static std::mutex s_mutex;
    static std::unique_ptr<CImprimirBJust> s_inst;
};

} // namespace vota
