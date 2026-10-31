#pragma once

#include <string>

#include "app/comum/gravadores/igravadorenvelope.h"

namespace comum {

// RTTI: an si_class of comum::IGravadorEnvelope. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorEnvelopeArquivo), whose control block's __on_zero_shared is the shared call
// through the vtable (fn 172), so the class is not final. Recovered: the layout, 184 bytes (12098 allocates it with
// f137(184)), and the virtual members. The constructor (fn 5856) builds IGravadorEnvelope's members, stores this vptr
// and copies its last argument, a string, to +172. The destructor is not declared (implicit): the base-object one (fn
// 11622, slot 0) frees that string and holds IGravadorEnvelope's inline, the deleting one (fn 11621, slot 1) the same
// body and the free of `this`. Slot 7 is IGravadorEnvelope's (fn 11626); slot 8 (fn 11623) is out of line, so it is
// the key function; it is not reconstructed, and no record names this class's file (the path follows igravador.h).
// The constructor is not declared; the string's role and the member name are chosen.
class CGravadorEnvelopeArquivo : public IGravadorEnvelope {
public:
    virtual void Slot8() override;

private:
    std::string m_nomeArquivoEnvelope;
};

} // namespace comum
