#pragma once

#include "app/comum/cappstate.h"
#include "ecourna/api/uetypes.hpp"

namespace vota {

// vota::CEleitorVotando (RTTI: si_class of comum::CAppState; vtable @1533144 [2483, 7385, 7377, 7352, 1661, 7370, 7337,
// 7345, 7349]): the state that runs one voter's vote, holding the state of the post being voted at +12, whose
// FinishState and StartState it calls when it moves to the next post, and to which it passes its input and ticks. The
// records of celeitorvotando.cpp name IniciaCiclo (:125 and :131, held by slot 2, fn 7377), ChamaEstadoProximoCargo
// (:229, fn 4459), DescartaVotos (:253 and :254, fn 4449), NeedChangeState (:294, slot 3, fn 7352) and
// suspenderEleitor(const EOrigemSuspensao) (:410 and :427, fn 4442).
//
// Written: ChamaEstadoProximoCargo, ProcessInput (slot 7, fn 7345) and ProcessTick (slot 8, fn 7349). Pending
// (src/units/197-uenux2-celeitorvotando-pending.cpp): the destructor, StartState, NeedChangeState, FinishState and
// ProcessKey. The destructor is out of line (the D0, fn 7385, calls the D2, fn 2483, and frees `this`:
// docs/reference/facts/reading.md R5) and the D2 stores no vptr, so the class is final (R4); declared first, it is the
// key function, a choice, so the pending object emits the vtable.
//
// The layout, as far as the written members read it: +12 the post's state; +16 the id of a tick the slots stop and
// start again (fns 422 and 700, CThreadVota's StopTick and StartTick, on CThreadEleitor::GetInst()); +17 a flag
// ProcessTick sets when that tick runs out and ProcessInput and ProcessKey clear. Not declared: +18, a flag slot 2 sets
// and NeedChangeState tests, and +20, a member whose destructor is fn 1468 (the D2 calls it on +20) and whose type no
// header of this tree holds. So the head is not complete: nothing may construct it. The members' names, ProcessKey's
// parameter name, that ChamaEstadoProximoCargo is private (its two callers, fns 7352 and 7377, are the class's), and
// this header's path beside celeitorvotando.cpp, are chosen.
class CEleitorVotando final : public comum::CAppState {
public:
    virtual ~CEleitorVotando() override;

    virtual void StartState() override;

    virtual bool NeedChangeState() override;

    virtual void FinishState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte tick) override;

private:
    void ChamaEstadoProximoCargo();

    comum::CAppState* m_pEstado;
    uebyte m_tick;
    bool m_emSuspensao;
};

} // namespace vota
