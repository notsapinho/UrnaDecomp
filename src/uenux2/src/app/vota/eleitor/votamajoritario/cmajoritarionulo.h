#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/votamajoritario/cconfirmamajoritario.h"

namespace vota {

// vota::CMajoritarioNulo (RTTI: si_class of vota::CConfirmaMajoritario; vtable @1550004): overrides slot 15 (fn 11693,
// which returns one of two messages by comum::CCargos::GetInst().GetCurrent().IsConsulta()) and the destructors (fns
// 884 and 883, the bodies of fifteen states, whose out-of-line form unit 97's fragment reads). A singleton: GetInst,
// out of line here, is held inlined by fn 11672, slot 16 of the CConfereVotoEmCargo class over it, a thunk into fn
// 2901, the body binaryen shares for that slot of the four majority states; it passes the constructor's arguments
// (EVENTO_ENTRADA | EVENTO_TICK, 6, 4), the static std::mutex (@1838232) and std::unique_ptr (@1838256) and the vptr.
// final, as the shared body deletes the old object through CVotacaoStateAudio's D2. Unit 104's singletons give the
// form. The name of slot 15 and this header's path are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CMajoritarioNulo final : public CConfirmaMajoritario {
public:
    virtual ~CMajoritarioNulo() override;

    static CMajoritarioNulo& GetInst();

    virtual std::string GetMensagem() const override;

private:
    CMajoritarioNulo();

    static std::mutex s_mutex;
    static std::unique_ptr<CMajoritarioNulo> s_inst;
};

} // namespace vota
