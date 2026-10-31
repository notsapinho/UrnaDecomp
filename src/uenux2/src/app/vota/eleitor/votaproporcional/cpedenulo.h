#pragma once

#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"

namespace vota {

// vota::CPedeNulo (RTTI: si_class of vota::CCompletaProporcional; vtable @1548524): overrides slot 15 (fn 11745), slot 16
// (fn 11744, record cpedenulo.cpp:44: pending) and the destructors (fns 884 and 883, the bodies of fifteen states, whose out-of-line form
// unit 97's fragment reads). Its singleton builder is not reconstructed, so sizeof is wrong and nothing may construct the
// class. The name of slot 15 and this header's path are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CPedeNulo : public CCompletaProporcional {
public:
    virtual ~CPedeNulo() override;

    virtual std::string GetMensagem() const override;

    virtual comum::CAppState* GetProximoEstado(const std::string& numero) const override;
};

} // namespace vota
