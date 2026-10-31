#pragma once

#include "app/comum/gravadores/igravadorenvelope.h"

namespace comum {

// RTTI: an si_class of comum::IGravadorEnvelope. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorEnvelopeArquivo), whose control block's __on_zero_shared is the shared call
// through the vtable (fn 172), so the class is not final. Recovered: the head only, which is all that block needs; the
// constructor, the members and the slots are not reconstructed (no record: the path follows igravador.h).
class CGravadorEnvelopeArquivo : public IGravadorEnvelope {};

} // namespace comum
