#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/votaproporcional/cconfirmaproporcional.h"

namespace vota {

// vota::CConfirmaVotoLegenda (RTTI: si_class of vota::CConfirmaProporcional; vtable @1548804): overrides slot 15 (fn
// 11735) and the destructors (fns 884 and 883, which binaryen keeps once for the fifteen states of this shape). The
// destructor is out of line: fn 884 is a body of one call of the base's D2, where an implicit destructor leaves the
// base's D2 itself in the slot, as vota::CConfirmaProporcional's does. Fn 883 is the object's D0, a call of the D1 and
// a free of `this`, with that one call inlined by binaryen. Declared first, the destructor is the key function, a
// choice. A singleton: GetInst, out of line here, is held inlined by fn 11717, slot 16 of the CConfereVotoEmCargo class
// over it, a thunk into fn 1961, the body binaryen shares for that slot of the six proportional states; it passes the
// constructor's arguments (9, 1), the static std::mutex (@1837864) and std::unique_ptr (@1837888) and the vptr. final,
// as the shared body deletes the old object through CVotacaoStateAudio's D2. Unit 104's singletons give the form. The
// file, this header's path and the name of slot 15 are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CConfirmaVotoLegenda final : public CConfirmaProporcional {
public:
    virtual ~CConfirmaVotoLegenda() override;

    static CConfirmaVotoLegenda& GetInst();

    virtual std::string GetMensagem() const override;

private:
    CConfirmaVotoLegenda();

    static std::mutex s_mutex;
    static std::unique_ptr<CConfirmaVotoLegenda> s_inst;
};

} // namespace vota
