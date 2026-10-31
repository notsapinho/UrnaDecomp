#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/votaproporcional/cconfirmaproporcional.h"

namespace vota {

// vota::CConfirmaVotoNominal (RTTI: si_class of vota::CConfirmaProporcional; vtable @1548988): overrides slot 15 (fn
// 11728), slot 17 (fn 5925, the body vota::CMajoritarioValido's slot 17 holds too: pending) and the destructors (fns
// 884 and 883, the bodies of fifteen states, whose out-of-line form unit 97's fragment reads). A singleton: GetInst,
// out of line here, is held inlined by fn 11715, slot 16 of the CConfereVotoEmCargo class over it, a thunk into fn
// 1961, the body binaryen shares for that slot of the six proportional states; it passes the constructor's arguments
// (1, 2), the static std::mutex (@1837920) and std::unique_ptr (@1837944) and the vptr. final, as the shared body
// deletes the old object through CVotacaoStateAudio's D2. Unit 104's singletons give the form. The name of slot 15 and
// this header's path are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CConfirmaVotoNominal final : public CConfirmaProporcional {
public:
    virtual ~CConfirmaVotoNominal() override;

    static CConfirmaVotoNominal& GetInst();

    virtual std::string GetMensagem() const override;

    virtual void AoConcluirEntrada(api::EInputResult resultado) override;

private:
    CConfirmaVotoNominal();

    static std::mutex s_mutex;
    static std::unique_ptr<CConfirmaVotoNominal> s_inst;
};

} // namespace vota
