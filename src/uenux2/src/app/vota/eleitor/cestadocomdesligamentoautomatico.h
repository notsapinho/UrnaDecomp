#pragma once

#include "api/util/cdatetime.h"
#include "app/comum/cappstate.h"

namespace vota {

// vota::CEstadoComDesligamentoAutomatico (RTTI: si_class of comum::CAppState; vtable @1541900 [174, 325, 12143, 7480,
// 1661, 218, 425, 218, 12061, 425]): the states that shut the machine down on a time limit. Abstract, as StartState
// stays pure, with an implicit destructor: slot 0 holds comum::CAppState's D2 (fn 174). ProcessTick (fn 12061, record
// cestadocomdesligamentoautomatico.cpp:44, of a lambda it holds inlined). The vtable and typeinfo lie just before that
// record, so a member is out of line in that file; ProcessTick, the one non-inline member declared, is the key function
// by choice. Slot 9 is what ProcessTick calls for any other tick's id: ProcessTickNaoDesligamento, the name the record
// of vota::CVerificaHorarioZeresima's override gives (cverificahorariozeresima.cpp:80, fn 11870); the base's body is
// the empty fn 425. The layout is what ProcessTick reads: +12 the limit, an api::CDateTime (fns 1000 and 759), +24 its
// tick id. The member names are chosen. The
// constructor (fn 1285, ten callers) passes its argument with the tick bit set to the base's, builds the limit from the
// time_t -1 and registers the 1000-ms tick on the CThreadEleitor (fn 4640 on fn 316's object). This header's path is
// chosen, beside that file.
class CEstadoComDesligamentoAutomatico : public comum::CAppState {
public:
    virtual void ProcessTick(uebyte tick) override;

    virtual void ProcessTickNaoDesligamento(uebyte) {}

protected:
    explicit CEstadoComDesligamentoAutomatico(int eventos);

    api::CDateTime m_limite;
    uebyte m_tick;
};

} // namespace vota
