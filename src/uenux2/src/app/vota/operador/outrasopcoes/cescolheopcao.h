#pragma once

#include <string>

#include "app/comum/cappstate.h"

namespace vota {

// RTTI: vota::CEscolheOpcao, an si_class of comum::CAppState (stub file cescolheopcao.cpp), and the name of its nested
// data source, which only the RTTI of api::CDataText<vota::CEscolheOpcao::COpcaoDS> gives (fn 2753 builds that text).
// Recovered: the names only, no member: the block's __on_zero_shared is the shared call through the vtable (fn 172), so
// it needs no more. A data source is callable; the call operator is declared and not reconstructed.
class CEscolheOpcao : public comum::CAppState {
public:
    class COpcaoDS {
    public:
        std::string operator()() const;
    };
};

} // namespace vota
