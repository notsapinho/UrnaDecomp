#pragma once

#include "app/comum/gravadores/igravador.h"

namespace comum {

// RTTI: an si_class of comum::IGravador, vtable @1554448 [11625, 325, ...], an abstract class with one pure slot more
// (slot 8). Recovered: the head only, as far as CGravadorEnvelopeArquivo needs its base. The path is chosen, beside
// igravador.h: no record names it.
class IGravadorEnvelope : public IGravador {};

} // namespace comum
