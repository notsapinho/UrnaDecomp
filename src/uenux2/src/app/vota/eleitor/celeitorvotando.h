#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "api/gui/capplicationcontext.h"
#include "app/comum/cappstate.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvoto.h"
#include "ecourna/api/uetypes.hpp"

namespace vota {

// vota::CEleitorVotando (RTTI: si_class of comum::CAppState; vtable @1533144 [2483, 7385, 7377, 7352, 1661, 7370, 7337,
// 7345, 7349]): the state that runs one voter's vote, holding the state of the post being voted at +12, whose
// FinishState and StartState it calls when it moves to the next post, and to which it passes its input and ticks. The
// records of celeitorvotando.cpp name IniciaCiclo (:125 and :131, held by slot 2, fn 7377), ChamaEstadoProximoCargo
// (:229, fn 4459), DescartaVotos (:253 and :254, fn 4449), NeedChangeState (:294, slot 3, fn 7352) and
// suspenderEleitor(const EOrigemSuspensao) (:410 and :427, fn 4442).
//
// Written: the constructor (held inlined by GetInst, fn 3229), GetInst, the destructor (D2 fn 2483, D0 fn 7385),
// RegistraVoto (fn 4471), FinishState (slot 5, fn 7370), ChamaEstadoProximoCargo, ProcessInput (slot 7, fn 7345) and
// ProcessTick (slot 8, fn 7349). Pending (src/units/197-uenux2-celeitorvotando-pending.cpp): StartState,
// NeedChangeState and ProcessKey. The destructor is out of line (the D0 calls the D2 and frees `this`:
// docs/reference/facts/reading.md R5) and the D2 stores no vptr, so the class is final (R4); declared first, it is the
// key function, a choice, so this class's own object emits the vtable.
//
// The layout is what the constructor stores (fn 3229 allocates 72 bytes): +12 the post's state (0); +16 the id of a
// tick the constructor takes from CThreadEleitor (fn 807, CThreadVota::AddStoppedTick) and the slots stop and start
// again (fns 422 and 700); +17 a flag ProcessTick sets when that tick runs out and ProcessInput and ProcessKey clear
// (0); +18 a flag slot 2 sets when it hands over to vota::CInstrucaoVotacaoAcessibilidade and NeedChangeState tests
// and clears (0); +20 the api::CApplicationContext the constructor builds with api::CriaContextoAplicacao (fn 3682),
// which slot 2 pushes (fn 3684, CApplication::PushContext, on a copy, fn 1841) and FinishState takes back out (fn
// 5553, CApplicationContextStack::Pop), and the D2 destroys (fn 1468). The members' names, ProcessKey's parameter name,
// that ChamaEstadoProximoCargo is private (its two callers, fns 7352 and 7377, are the class's), and this header's path
// beside celeitorvotando.cpp, are chosen.
class CEleitorVotando final : public comum::CAppState {
public:
    virtual ~CEleitorVotando() override;

    static CEleitorVotando& GetInst();

    // fn 4471: appends the post's vote (vota::AdicionaVoto, fn 4192) and logs it by its kind through CLogVota: fns
    // 4546, 4541, 4542 and 3272 for the kinds 5, 6, 8 and 9, fn 4537 for any other. Its two callers, fns 7428 and
    // 11754, call GetInst and drop the result just before they call it, the call of a member that reads no member
    // (binaryen drops the unused `this`, in our link as in the target), and suspenderEleitor (fn 4442) holds the same
    // calls. Its name, its parameters' names and that it is not static (not measured) are chosen.
    void RegistraVoto(comum::md::TCargoID cargo, comum::md::CVoto::ETipo tipo, const std::string& numero);

    virtual void StartState() override;

    virtual bool NeedChangeState() override;

    virtual void FinishState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte tick) override;

private:
    CEleitorVotando();

    void ChamaEstadoProximoCargo();

    comum::CAppState* m_pEstado;
    uebyte m_tick;
    bool m_emSuspensao;
    bool m_vindoDaInstrucao;
    api::CApplicationContext m_contexto;

    static std::unique_ptr<CEleitorVotando> s_inst;
    static std::mutex s_mutex;
};

// The line the operator's screen shows for the post being voted: "VOTANDO PARA: " and the post's name, with the ordinal
// of the choice for a post of several choices, cut to 40 characters (fn 4464; its callers are NeedChangeState and slot
// 2, fns 7352 and 7377). It reads no state of CEleitorVotando, so it is a free function; its name, its namespace and
// that it is external are chosen.
void MostraCargoNoOperador(const comum::md::CCargo& cargo);

} // namespace vota
