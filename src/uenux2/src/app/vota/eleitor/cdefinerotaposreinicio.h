#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CDefineRotaPosReinicio (RTTI: si_class of comum::CAppState; vtable @1546124 [174, 144, 3243, 11858, 1661, 218,
// 425, 5974, 425]): it overrides StartState (slot 2), NeedChangeState (slot 3) and ProcessInput (slot 7). The 16-byte
// object adds a pointer at +12, which the constructor and NeedChangeState (fn 11858, record 81) clear. ProcessInput
// (fn 5974, one body with vota::CDefineRotaPreVotacao's) calls slot 7 through it when it is not null; that slot is
// comum::CAppState's ProcessInput, which is all that says its type, so comum::CAppState* is chosen. StartState (fn
// 3243, one body with vota::CAguardaMensagem's and vota::CDefineRotaPreVotacao's) sets the next state to this state.
// final: fn 5943 deletes the old object with no call through the vtable. A singleton: GetInst (fn 5943) keeps the
// object in a static std::unique_ptr (@1834772, destroyed at exit by fn 11860) under a static std::mutex (@1834748, by
// fn 11859). The constructor passes 7 to the base's. src/units/104-uenux2-app-vota-estados.mk says which of this is
// evidence and which is chosen.
class CDefineRotaPosReinicio final : public comum::CAppState {
public:
    static CDefineRotaPosReinicio& GetInst();

    virtual void StartState() override;

    virtual bool NeedChangeState() override;

    virtual void ProcessInput() override;

private:
    CDefineRotaPosReinicio();

    static std::mutex s_mutex;
    static std::unique_ptr<CDefineRotaPosReinicio> s_inst;

    comum::CAppState* m_pEstado;
};

} // namespace vota
