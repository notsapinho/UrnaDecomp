#pragma once

#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"

namespace vota {

// vota::CPedeNominal (RTTI: si_class of vota::CCompletaProporcional; vtable @1549080): overrides slot 15 (fn 11725),
// slot 16 (fn 11724, no record: pending) and the destructors (fns 884 and 883, the bodies of fifteen states, whose
// out-of-line form unit 97's fragment reads). Its singleton builder is not written, and nothing here constructs the
// class; its size is not read. The name of slot 15 and this header's path are chosen
// (src/units/97-uenux2-cvotacaostateaudio.mk).
class CPedeNominal : public CCompletaProporcional {
public:
    virtual ~CPedeNominal() override;

    virtual std::string GetMensagem() const override;

    virtual comum::CAppState* GetProximoEstado(const std::string& numero) const override;
};

} // namespace vota
