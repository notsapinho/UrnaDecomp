#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CPedeProporcional (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1549432 [884, 883, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11711, 11712, 218, 425, 3139, 6999, 11710]): the state that asks for a proportional vote. It
// overrides slots 9 and 10 (fns 11711, record cpedeproporcional.cpp:84, and 11712: pending), 12 (empty, fn 425) and 15
// (fn 11710), and the destructors: fns 884 and 883, the bodies of fifteen states, whose out-of-line form unit 97's
// fragment reads. A singleton: GetInst (fn 3849, a thunk into fn 6051, the body binaryen shares with
// vota::CPedeMajoritario::GetInst, fn 5921) builds the one 28-byte object, the base's size, under a static std::mutex
// (@1838084) and keeps it in a static std::unique_ptr (@1838108); the constructor, inlined there, passes 2 to the
// base's. final: fn 6051 deletes the old object through CVotacaoStateAudio's D2 (fn 1035), with no call through the
// vtable. GetInst, its statics and the constructor follow unit 104's singletons (src/units/104-uenux2-app-vota-estados.mk
// has the evidence for that form); the names of slot 15 and the statics, and this header's path, are chosen.
class CPedeProporcional final : public CVotacaoStateAudio {
public:
    virtual ~CPedeProporcional() override;

    static CPedeProporcional& GetInst();

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual std::string GetMensagem() const override;

private:
    CPedeProporcional();

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeProporcional> s_inst;
};

} // namespace vota
