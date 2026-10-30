#pragma once

#include "app/vota/eleitor/votaproporcional/cconfirmaproporcional.h"

namespace vota {

// vota::CProporcionalBranco (RTTI: si_class of vota::CConfirmaProporcional; vtable @1549636): overrides slot 15 (fn 11704) and the destructors
// (fns 884 and 883, which binaryen keeps once for the fifteen states of this shape). The destructor is out of line: fn
// 884 is a body of one call of the base's D2, where an implicit destructor leaves the base's D2 itself in the slot, as
// vota::CConfirmaProporcional's does. Fn 883 is the object's D0, a call of the D1 and a free of `this`, with that one
// call inlined by binaryen. Declared first, the destructor is the key function, a choice. The constructor, inlined into
// the singleton builder binaryen shares as fn 1961, is not reconstructed, so sizeof is wrong and nothing may construct
// the class. The file, this header's path and the name of slot 15 are chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
class CProporcionalBranco : public CConfirmaProporcional {
public:
    virtual ~CProporcionalBranco() override;

    virtual std::string GetMensagem() const override;
};

} // namespace vota
