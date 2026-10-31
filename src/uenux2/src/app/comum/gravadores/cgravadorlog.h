#pragma once

#include <string>

#include "app/comum/gravadores/igravador.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorLog), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 76 bytes (12098 allocates it with f137(76)), and
// the virtual members. The constructor, which 12098 holds inlined, copies three strings to +40, +52 and +64, which the
// base-object destructor (fn 5823, slot 0) frees in reverse. The destructor is defined in the class without `inline`:
// the deleting one (fn 11583, slot 1) calls the base-object one and frees what it returns, where the implicit
// destructor, measured in this unit's link, inlines that body into it (docs/reference/facts/reading.md R5). R5's probe
// gives `= default` and `{}` the same object; `= default` is a choice. GravaResultado (slot 7, fn 11584) is out of line, so it is the key
// function; it is not reconstructed, and no record names this class's file (the path follows igravador.h). The
// constructor is not declared; the strings' roles and every member name are chosen.
class CGravadorLog : public IGravador {
public:
    ~CGravadorLog() override = default;

    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    std::string m_arquivoLog;
    std::string m_arquivoLogComum;
    std::string m_arquivoLogSeguranca;
};

} // namespace comum
