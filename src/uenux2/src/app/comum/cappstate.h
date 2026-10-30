#pragma once

#include "api/pattern/cstate.h"
#include "ecourna/api/uetypes.hpp"

// comum::CAppState: the base of every state of the applications' state machines (RTTI: si_class of api::CState,
// ledger/classes.json; vtable @1551240 [174, 325, 12143, 7480, 1661, 218, 425, 218, 425], ledger/vtables.json), run by
// comum::CAppStateContext. 198 classes derive from it.
//
// The slots: 0 and 1 the destructors (fn 174 returns `this`; fn 325, a trap, is the deleting destructor of an abstract
// class); 2 StartState, pure (fn 12143); 3 NeedChangeState (fn 7480: the next state is not this one); 4 the next state
// (fn 1661 returns +4); 5 FinishState, 6, 7 ProcessInput and 8 ProcessTick(uebyte), empty (fns 218 and 425). The names
// of slots 2, 3, 5, 7 and 8 and their types are the overriders' records' (StartState in 39 files, among them
// cexibealertadesligamento.cpp:45; NeedChangeState in celeitorvotando.cpp:294 and cdefinerotaposreinicio.cpp:81;
// FinishState in cpededigital.cpp:131; ProcessInput in cvotacaostateaudio.cpp:69; ProcessTick(uebyte) in
// cexibealertadesligamento.cpp:53). No record, symbol or caller names slots 4 and 6: GetNextState and ProcessKey are
// chosen from what CAppStateContext does with them (fn 4349, CThreadEleitor::ProcessarEntrada, record
// cthreadeleitor.cpp:134, with the context's members inlined): it changes state as
// `if (s->NeedChangeState()) { s->FinishState(); s = s->GetNextState(); if (s) s->StartState(); }`, passes each key it
// reads to slot 6 with the key's low byte (its overriders compare it with key codes: fn 11794 with 13), calls slot 7
// when the keyboard has input and slot 8 with each tick's id. Every derived vtable (196) holds fn 1661 in slot 4.
//
// The layout is what the constructor (fn 224) stores: +4 the next state, which it sets to `this` and the derived states
// set (fn 12018 stores `this`, fn 12017 another state); +8, +9 and +10 three flags, bits 0, 1 and 2 of its argument,
// which the context reads before calling slots 6, 7 and 8 (fns 3842, 5909 and 5908 load +8, +9 and +10). The member
// names, the enumeration of the bits and the argument's type are chosen; the target's callers pass every value from 0
// to 7 (`awk -F'\t' '$2==224' ledger/callgraph.tsv`, 97 callers).
//
// Out of line, in app/comum/cappstate.cpp: the constructor (97 derived constructors call fn 224 before storing their
// own vptr) and the destructor. A member of the class is out of line, as the key function: the typeinfo (@1551284) is
// emitted with the vtable, not in the first derived class's object (vota::CAguardaMensagem, typeinfo @1533000), where a
// class with no key function gets it (api::ITimer's @1532124 follows simulador::CWasmTimer's @1532112). Which member is
// not recorded (slots 0, 1, 5 to 8 are bodies other classes share); the destructor is chosen. NeedChangeState is inline:
// fn 7480 lies among caguardamensagem.cpp's functions in the target's order (fns 7479 to 7482). The directory and file
// name: the vtable and typeinfo lie between comum::CAbstractTelaProgresso's (@1551204) and the records of
// app/comum/carquivosresultado.cpp (@1551340), with comum::CAppStateContext's vtable after them, in the name order the
// root of app/comum/ links in (carquivossavd, cinfomtlcd, cpacotearquivos, cpath, iinterfaceinit follow).

namespace comum {

class CAppState : public api::CState {
public:
    // The bits of the constructor's argument: the events the state receives (names chosen).
    enum EEvento {
        EVENTO_NENHUM = 0x0,
        EVENTO_TECLA = 0x1,
        EVENTO_ENTRADA = 0x2,
        EVENTO_TICK = 0x4,
    };

    virtual ~CAppState() override;

    virtual void StartState() = 0;

    virtual bool NeedChangeState() { return GetNextState() != this; }

    virtual CAppState* GetNextState() { return m_pNextState; }

    virtual void FinishState() {}

    virtual void ProcessKey(uebyte) {}

    virtual void ProcessInput() {}

    virtual void ProcessTick(uebyte) {}

protected:
    explicit CAppState(int eventos);

    CAppState* m_pNextState;

private:
    bool m_bTecla;
    bool m_bEntrada;
    bool m_bTick;
};

} // namespace comum
