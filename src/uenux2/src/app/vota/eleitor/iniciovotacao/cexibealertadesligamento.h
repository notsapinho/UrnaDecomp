#pragma once

#include <memory>

#include "api/util/cdatetime.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CExibeAlertaDesligamento (RTTI: si_class of comum::CAppState; vtable @1543004 [2883, 12019, 12018, 7480, 1661,
// 218, 425, 218, 12017]): it overrides the destructors, StartState (record cexibealertadesligamento.cpp:45) and
// ProcessTick (records :53 and :54). A singleton: fn 5979 creates the one 40-byte object on first use, unlocks a static
// std::mutex (@1833992, destroyed at exit by fn 12021) and keeps the object in a static std::unique_ptr (@1834016,
// destroyed at exit by fn 12022, which calls this destructor as fn 5979 does). The constructor, inlined
// there, passes comum::CAppState::EVENTO_TICK (4) to the base constructor (fn 224) and stores what the layout below
// holds. Recovered: the layout and the destructor, out of line (the deleting one, fn 12019, calls it). Declared first,
// it is the key function and cexibealertadesligamento.cpp emits the vtable: a choice, as StartState and ProcessTick are
// out of line in the same file too and the target does not show the declaration order. It stores no vptr, which clang
// leaves out of a destructor that destroys members only when the class is final. Not recovered: the constructor,
// GetInst (fn 5979; its name follows the project's other singletons; of its callees 1000 and 316 match, 4640 has no name)
// and the two overriders (pending, src/units/61-uenux2-cexibealertadesligamento-pending.cpp).
//
// The layout: +12 an api::CDateTime (fn 1000, CDateTime's constructor from a time_t, which calls ConvertFromLocalTime,
// fn 5476, builds it with -1; StartState copies a 12-byte static into it and ProcessTick compares it with the current
// time through fn 759, the CDateTime comparison); +24 a std::shared_ptr copied from vota::CTelasVota::GetInst()'s +44
// (fn 407), whose slot 2 StartState calls with no argument: the pointee's type is chosen (api::IForm<api::IScreen>,
// the type vota::CProgressoEncerramento's form has), nothing here names it; +32 the id of the 1000-ms tick the
// constructor registers (fn 4640 on fn 316's object), which ProcessTick compares with its argument; +36 the state
// ProcessTick goes to, which fn 12061 sets. The member names are not in the target.
class CExibeAlertaDesligamento final : public comum::CAppState {
public:
    virtual ~CExibeAlertaDesligamento() override;

    static CExibeAlertaDesligamento& GetInst();

    virtual void StartState() override;

    virtual void ProcessTick(uebyte tick) override;

private:
    CExibeAlertaDesligamento();

    api::CDateTime m_limite;
    std::shared_ptr<api::IForm<api::IScreen>> m_form;
    uebyte m_tick;
    comum::CAppState* m_pProximoEstado;
};

} // namespace vota
