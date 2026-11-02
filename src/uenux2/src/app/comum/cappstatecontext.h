#pragma once

#include "api/pattern/cstatecontext.h"
#include "app/comum/cappstate.h"
#include "ecourna/api/uetypes.hpp"

// comum::CAppStateContext, the context the vota threads run their comum::CAppState machines in (RTTI: si_class of
// api::CStateContext<comum::CAppState>, ledger/classes.json). Its vtable @1551304 holds the shared bodies 174 and 144, so
// the class has a virtual destructor that destroys nothing. vota::CThreadVota holds one in a std::unique_ptr at +32,
// which fn 2126 frees through slot 1, and the threads' Run build it (fn 3844 in 7061 and 10204). No record names this
// header, so its path is chosen, beside app/comum/cappstate.h, whose vtable and typeinfo lie just before this class's.
//
// Recovered: +4, the state, which the constructor (fn 3844) stores and every member reads first, and the members of
// app/comum/cappstatecontext.cpp, which are out of line (src/units/168-uenux2-app-helpers.mk says why). That this class
// and not its base holds +4 is chosen. When there is a state, the members call its slots 6, 7 and 8 (fns 3843, 5911,
// 5910) or read its three flags (fns 3842 +8, 5909 +9, 5908 +10), as CAppState's friend (cappstate.h). The names of the
// members and of m_estado are chosen; ProcessKey's uebyte is the type of the slot it calls, and an int gives another
// body (the fragment says so); ProcessTick's uebyte is read the same way, not measured.
//
// TrocaEstado: fns 4349 and 10204 (vota::CThreadEleitor's and vota::CThreadOperador::Run) hold, after each key, input
// and pass of ticks they hand the state, the same code that changes state: when there is a state and its slot 3
// (NeedChangeState) is true, its slot 5 (FinishState), then +4 = its slot 4 (GetNextState), then that state's slot 2
// (StartState) unless it is null, +4 loaded again after each call. It is no function of its own in the target, and
// fn 10204 holds it four times (a reading: binaryen inlines a function of one call site only, so clang inlined it).
// The member and its name are chosen.
//
// GetState: fn 4705 (slot 9 of vota::CExecucaoVota and of vota::CExecucaoVotaCooperativa) reads +4 of the context the
// thread holds at +32, and fn 4713 reads it after building a new context, each in its own code (no call), so code
// outside this class reads the state. That it does so through a public inline accessor, and its name, are chosen.

namespace comum {

class CAppStateContext : public api::CStateContext<CAppState> {
public:
    explicit CAppStateContext(CAppState* estado);

    void ProcessKey(uebyte tecla);

    void ProcessInput();

    void ProcessTick(uebyte tick);

    bool AcceptsKey() const;

    bool AcceptsInput() const;

    bool AcceptsTick() const;

    CAppState* GetState() const { return m_estado; }

    void TrocaEstado()
    {
        if (m_estado && m_estado->NeedChangeState()) {
            m_estado->FinishState();
            m_estado = m_estado->GetNextState();
            if (m_estado) {
                m_estado->StartState();
            }
        }
    }

private:
    CAppState* m_estado;
};

} // namespace comum
