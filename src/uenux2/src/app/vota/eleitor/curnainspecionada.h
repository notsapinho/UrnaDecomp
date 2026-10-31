#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CUrnaInspecionada (RTTI: si_class of comum::CAppState; vtable @1547520 [448, 765, 1718, 7480, 1661, 218, 11794,
// 218, 425]). It overrides the destructors, StartState (slot 2, fn 1718, one body with the slot 2 of six other states)
// and ProcessKey (slot 6, fn 11794). The 28-byte object (fn 11797 allocates 28 bytes for it) adds two std::shared_ptr:
// +12, the form StartState shows, and +20, the form ProcessKey shows when the key is 13. fn 11797 fills them after
// calling vota::CTelasVota::GetInst (fn 407): +12 through fn 2380, +20 through fn 6557, which calls fn 2380, and fn 2380
// builds an api::CFormBuilder (fn 203). So their pointee's type, api::IForm<api::IScreen>, is chosen after that
// builder's GetForm. The destructor is out of line: the deleting one (fn 765) calls it and frees `this`, and it stores
// no vptr, as a final class's; 19 states share the two bodies, fns 448 and 765. A singleton: fn 11797 creates the object
// on first use and keeps it in a static std::unique_ptr (@1837732) under a static std::mutex (@1837708), destroyed at
// exit by fns 11796 and 11795; the constructor passes comum::CAppState::EVENTO_TECLA (1) to the base's. Not recovered:
// the constructor, GetInst and the statics (fn 11797, which holds them inlined, calls fns 501, 2380 and 6557, which have
// no name). src/units/142-uenux2-app-vota-estados-448.mk says which of this is evidence and which is chosen.
class CUrnaInspecionada final : public comum::CAppState {
public:
    virtual ~CUrnaInspecionada() override;

    static CUrnaInspecionada& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

private:
    CUrnaInspecionada();

    std::shared_ptr<api::IForm<api::IScreen>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formConfirmacao;
};

} // namespace vota
