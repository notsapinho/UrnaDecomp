#pragma once

#include "app/comum/gravadores/igravador.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorHashes), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the head only, which is all that block needs; the
// constructor, the members and the slots are not reconstructed (the file is the header of cgravadorhashes.cpp, which its record names).
class CGravadorHashes : public IGravador {};

} // namespace comum
