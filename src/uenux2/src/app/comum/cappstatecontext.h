#pragma once

#include "api/pattern/cstatecontext.h"
#include "ecourna/api/uetypes.hpp"

// comum::CAppStateContext, the context the vota threads run their comum::CAppState machines in (RTTI: si_class of
// api::CStateContext<comum::CAppState>, ledger/classes.json). Its vtable @1551304 holds the shared bodies 174 and 144, so
// the class has a virtual destructor that destroys nothing. vota::CThreadVota holds one in a std::unique_ptr at +32,
// which fn 2126 frees through slot 1, and the threads' Run build it (fn 3844 in 7061 and 10204). No record names this
// header, so its path is chosen, beside app/comum/cappstate.h, whose vtable and typeinfo lie just before this class's.
//
// Recovered: +4, the state, which the constructor (fn 3844) stores and every member reads first, and the members of
// app/comum/cappstatecontext.cpp, which are out of line (src/units/168-uenux2-app-helpers.mk says why). That this class
// and not its base holds +4 is chosen. The target's other members read the state's three flags (fn 3842 +8, 5909 +9,
// 5908 +10) or call its slots 7 and 8 (5911, 5910) when there is a state. None of those five is written here: the
// flags are private to CAppState and its header has no friend or accessor for them. The names of the members and of
// m_estado are chosen; ProcessKey's uebyte is the type of the slot it calls, and an int gives another body (the
// fragment says so). The code that changes state, inlined into fn 4349, is not reconstructed.

namespace comum {

class CAppState;

class CAppStateContext : public api::CStateContext<CAppState> {
public:
    explicit CAppStateContext(CAppState* estado);

    void ProcessKey(uebyte tecla);

private:
    CAppState* m_estado;
};

} // namespace comum
