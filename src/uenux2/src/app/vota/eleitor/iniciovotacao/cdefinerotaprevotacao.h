#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CDefineRotaPreVotacao (RTTI: si_class of comum::CAppState; vtable @1543448 [174, 144, 3243, 11994, 1661, 218,
// 425, 5974, 425]): vota::CDefineRotaPosReinicio's sibling, with the same shape. It overrides StartState (slot 2) and
// ProcessInput (slot 7), whose bodies are vota::CDefineRotaPosReinicio's (fns 3243 and 5974, one body for both
// classes, binaryen's merge of identical functions), and NeedChangeState (slot 3, fn 11994). The 16-byte object adds a
// pointer at +12, which the constructor and NeedChangeState clear and ProcessInput calls slot 7 through when it is not
// null (comum::CAppState* chosen, as in vota::CDefineRotaPosReinicio). A singleton: GetInst, inlined by binaryen into
// its one caller, vota::CImprimindoZeresima::StartState (fn 11991), builds the object over the base's constructor with
// 7 and keeps it in a static std::unique_ptr (@1834072, destroyed at exit by fn 11996) under a static std::mutex
// (@1834048, by fn 11995); it deletes the old object with no call through the vtable, so final. Slots 0 and 1 hold the
// destructors the states with no member to destroy share (fns 174 and 144). The member's name, GetInst's, the
// statics', StartState as the key function and this header's path, beside the .cpp, are chosen
// (src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk says why the file is there).
class CDefineRotaPreVotacao final : public comum::CAppState {
public:
    static CDefineRotaPreVotacao& GetInst();

    virtual void StartState() override;

    virtual bool NeedChangeState() override;

    virtual void ProcessInput() override;

private:
    CDefineRotaPreVotacao();

    static std::mutex s_mutex;
    static std::unique_ptr<CDefineRotaPreVotacao> s_inst;

    comum::CAppState* m_pEstado;
};

} // namespace vota
