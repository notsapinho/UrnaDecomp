#pragma once

#include "app/vota/eleitor/votamajoritario/cconfirmamajoritario.h"

namespace vota {

// vota::CMajoritarioValido (RTTI: si_class of vota::CConfirmaMajoritario; vtable @1550188): overrides slot 15 (fn 11687, which
// returns one of two messages by comum::CCargos::GetInst().GetCurrent().IsConsulta()) and slot 17 (fn 5925,
// the body vota::CConfirmaVotoNominal's slot 17 holds too: pending) and the destructors (fns 884
// and 883, the bodies of fifteen states, whose out-of-line form unit 97's fragment reads). Its singleton builder is not
// reconstructed, so sizeof is wrong and nothing may construct the class. The name of slot 15 and this header's path are
// chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CMajoritarioValido : public CConfirmaMajoritario {
public:
    virtual ~CMajoritarioValido() override;

    virtual std::string GetMensagem() const override;

    virtual void AoConcluirEntrada(api::EInputResult resultado) override;
};

} // namespace vota
