#pragma once

#include "app/comum/gravadores/igravador.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorRCSecao), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the head only, which is all that block needs; the
// constructor, the members and the slots are not reconstructed (the file is the header of cgravadorrcsecao.cpp, which its records name).
class CGravadorRCSecao : public IGravador {};

} // namespace comum
