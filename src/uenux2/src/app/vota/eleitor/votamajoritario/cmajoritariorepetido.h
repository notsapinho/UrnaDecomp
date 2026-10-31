#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/votamajoritario/cconfirmamajoritario.h"

namespace vota {

// vota::CMajoritarioRepetido (RTTI: si_class of vota::CConfirmaMajoritario; vtable @1550096): overrides slot 15 (fn
// 11690, which returns one of two messages by comum::CCargos::GetInst().GetCurrent().IsConsulta()) and the destructors
// (fns 884 and 883, the bodies of fifteen states, whose out-of-line form unit 97's fragment reads). A singleton:
// GetInst, out of line here, is held inlined by fn 11671, slot 16 of the CConfereVotoEmCargo class over it, a thunk
// into fn 2901, the body binaryen shares for that slot of the four majority states; it passes the constructor's
// arguments (EVENTO_ENTRADA | EVENTO_TICK, 15, 7), the static std::mutex (@1838260) and std::unique_ptr (@1838284) and
// the vptr. final, as the shared body deletes the old object through CVotacaoStateAudio's D2. Unit 104's singletons
// give the form. The name of slot 15 and this header's path are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CMajoritarioRepetido final : public CConfirmaMajoritario {
public:
    virtual ~CMajoritarioRepetido() override;

    static CMajoritarioRepetido& GetInst();

    virtual std::string GetMensagem() const override;

private:
    CMajoritarioRepetido();

    static std::mutex s_mutex;
    static std::unique_ptr<CMajoritarioRepetido> s_inst;
};

} // namespace vota
