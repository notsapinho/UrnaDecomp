#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CPedeMajoritario (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1550280 [884, 883, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11683, 11684, 218, 425, 3139, 6999, 11682]): the state that asks for a majority vote. It
// overrides slots 9 and 10 (fns 11683, records cpedemajoritario.cpp:64 and :125, and 11684: pending), 12 (empty, fn
// 425) and 15 (fn 11682, which returns one of two messages by comum::CCargos::GetInst().GetCurrent().IsConsulta()), and
// the destructors (fns 884 and 883, as vota::CPedeProporcional's). A singleton like that class: GetInst (fn 5921, a
// thunk into fn 6051) under a static std::mutex (@1838316) and a static std::unique_ptr (@1838340); its constructor
// passes 2 to the base's. vota::CPedeProporcional's header says what that form and final rest on; the names of slot 15
// and the statics, and this header's path, are chosen.
class CPedeMajoritario final : public CVotacaoStateAudio {
public:
    virtual ~CPedeMajoritario() override;

    static CPedeMajoritario& GetInst();

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual std::string GetMensagem() const override;

private:
    CPedeMajoritario();

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeMajoritario> s_inst;
};

} // namespace vota
