#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"

namespace vota {

// vota::CPedeNulo (RTTI: si_class of vota::CCompletaProporcional; vtable @1548524): overrides slot 15 (fn 11745), slot
// 16 (fn 11744, record cpedenulo.cpp:44, the throw of its EUeVotaError 9385) and the destructors (fns 884 and 883, the
// bodies of fifteen states, whose out-of-line form unit 97's fragment reads). A singleton in unit 104's form: GetInst
// builds the 32-byte object with CCompletaProporcional(5) under a static std::mutex (@1837764) and keeps it in a static
// std::unique_ptr (@1837788), whose exit destructors are fns 11746 and 11747; fn 11711, vota::CPedeProporcional's slot
// 9, holds GetInst and the constructor inlined, the one storer of this vptr, and deletes the old object through
// CVotacaoStateAudio's D2 (fn 1035) with no call through the vtable: final. The name of slot 15, the statics' names and
// this header's path are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CPedeNulo final : public CCompletaProporcional {
public:
    virtual ~CPedeNulo() override;

    static CPedeNulo& GetInst();

    virtual std::string GetMensagem() const override;

    virtual comum::CAppState* GetProximoEstado(const std::string& numero) const override;

private:
    CPedeNulo();

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeNulo> s_inst;
};

} // namespace vota
