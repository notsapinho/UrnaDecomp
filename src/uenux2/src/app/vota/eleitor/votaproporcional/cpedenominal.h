#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"

namespace vota {

// vota::CPedeNominal (RTTI: si_class of vota::CCompletaProporcional; vtable @1549080): overrides slot 15 (fn 11725),
// slot 16 (fn 11724, no record; its line in cpedenominal.cpp is a choice) and the destructors (fns 884 and 883, the bodies of fifteen states, whose
// out-of-line form unit 97's fragment reads). A singleton in unit 104's form: GetInst builds the 32-byte object with
// CCompletaProporcional(8) under a static std::mutex (@1837948) and keeps it in a static std::unique_ptr (@1837972),
// whose exit destructors are fns 11726 and 11727; fn 11711, vota::CPedeProporcional's slot 9, holds GetInst and the
// constructor inlined, the one storer of this vptr, and deletes the old object through CVotacaoStateAudio's D2 (fn
// 1035): final. The name of slot 15, the statics' names and this header's path are chosen
// (src/units/97-uenux2-cvotacaostateaudio.mk).
class CPedeNominal final : public CCompletaProporcional {
public:
    virtual ~CPedeNominal() override;

    static CPedeNominal& GetInst();

    virtual std::string GetMensagem() const override;

    virtual comum::CAppState* GetProximoEstado(const std::string& numero) const override;

private:
    CPedeNominal();

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeNominal> s_inst;
};

} // namespace vota
