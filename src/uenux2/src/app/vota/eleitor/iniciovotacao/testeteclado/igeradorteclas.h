#pragma once

// vota::testeteclado::impl::IGeradorTeclas, the keyboard test's key generator (RTTI: a class with no base, typeinfo
// @1547320). The path is chosen, beside ctesteteclado.cpp. Recovered: its one implementer, CGeradorTeclasAleatorio
// (vtable @1547288: the destructors, then slot 2), and what vota::testeteclado::CTesteTeclado::StartState (fn 11805)
// does with it. GetInst's record is ctesteteclado.cpp:121 (`static IGeradorTeclas &...::GetInst()`), the poly
// singleton's GetInst, which creates the default instance; slot 2 takes the key list by value (vota::
// SorteiaTeclasTesteTeclado, which StartState holds, copies the list into its frame for the call) and returns the
// sequence by value. Slot 2's name and its parameter's are chosen; that it is pure is chosen too: the one implementer
// overrides it. The destructor is declared first, so its slots come first in the vtable (the control block's
// __on_zero_shared calls vtable + 4).

#include <string>
#include <vector>

namespace vota::testeteclado::impl {

class IGeradorTeclas {
public:
    virtual ~IGeradorTeclas() = default;

    static IGeradorTeclas& GetInst();

    virtual std::vector<std::string> GeraSequencia(std::vector<std::string> teclas) = 0;
};

} // namespace vota::testeteclado::impl
