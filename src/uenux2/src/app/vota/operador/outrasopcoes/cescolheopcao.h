#pragma once

#include <functional>
#include <string>

#include "app/comum/cappstate.h"

namespace vota {

// RTTI: vota::CEscolheOpcao, an si_class of comum::CAppState (stub file cescolheopcao.cpp), and the name of its nested
// data source, which only the RTTI of api::CDataText<vota::CEscolheOpcao::COpcaoDS> gives (fn 2753 builds that text).
// CEscolheOpcao: the name only, no member.
//
// COpcaoDS: the layout is what the bodies give, 32 bytes. fn 2753 allocates its CDataText as 40 bytes and stores the
// source's int at +8 and a std::function at +16 (the copy of a std::function's buffer and target pointer); fn 10685,
// CDataText<COpcaoDS>::GetText, formats "{}-{}" with that int, as an int (argument type 3), and the std::string the
// std::function returns (type 13, called through slot 6 of its target, a bad_function_call when it is empty); the
// CDataText's D2 and D0 (fns 10688, 10686) destroy the std::function at +16. The members' names, their being public and
// the class's having no constructor of its own are chosen: no body shows a constructor. The call operator is defined in
// cescolheopcao.cpp, a choice: src/units/121-uenux2-datasources.mk has the other form that gives the same GetText.
class CEscolheOpcao : public comum::CAppState {
public:
    class COpcaoDS {
    public:
        std::string operator()() const;

        int m_numero;
        std::function<std::string()> m_texto;
    };
};

} // namespace vota
