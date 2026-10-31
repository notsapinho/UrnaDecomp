#pragma once

#include "app/vota/eleitor/votamajoritario/cconfirmamajoritario.h"

namespace vota {

// vota::CMajoritarioBranco (RTTI: si_class of vota::CConfirmaMajoritario; vtable @1549912): overrides slot 15 (fn 11696, which
// returns one of two messages by comum::CCargos::GetInst().GetCurrent().IsConsulta()) and the destructors (fns 884
// and 883, the bodies of fifteen states, whose out-of-line form unit 97's fragment reads). Its singleton builder is not
// reconstructed, so sizeof is wrong and nothing may construct the class. The name of slot 15 and this header's path are
// chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CMajoritarioBranco : public CConfirmaMajoritario {
public:
    virtual ~CMajoritarioBranco() override;

    virtual std::string GetMensagem() const override;
};

} // namespace vota
