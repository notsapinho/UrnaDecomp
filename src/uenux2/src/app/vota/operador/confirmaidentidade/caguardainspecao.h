#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CAguardaInspecao (RTTI: si_class of comum::CAppState; vtable @1590724 [244, 387, 1070, 7480, 1661, 218, 10530,
// 218, 425]): the operator's screen while the voter's side inspects the booth and the urna. It overrides the
// destructors, StartState (slot 2, fn 1070, the body twelve states' slot 2 share: the next state is this, then the
// form's slot 2) and ProcessKey (slot 6, fn 10530): on key 11 the next state is vota::CConfirmaInspecionada's. Slots 0
// and 1 are fns 244 and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at +12 is all they
// release, so the destructor is out of line (docs/reference/facts/reading.md R5) and the class final (R4). +12 is the
// form StartState shows, a plain one: the constructor builds it with api::CMTFormBuilder::GetForm (fn 1694). The object
// is 20 bytes. A singleton: GetInst and the constructor have no target index of their own: vota::CPedeIdentidade's
// ProcessTick (fn 10676) holds both inlined, the one store of this class's vptr (1590732): the object made under a
// static std::mutex (@1908528, destroyed at exit by fn 10531) and kept in a static std::unique_ptr (@1908552, by fn
// 10532), the constructor passing comum::CAppState::EVENTO_TECLA (1) to the base's and building the form from a helper,
// initialized in the member list (fn 1694 writes into the member).
// src/units/281-uenux2-cconfirmainspecionada.mk says which of this is evidence and which is chosen.
class CAguardaInspecao final : public comum::CAppState {
public:
    virtual ~CAguardaInspecao() override;

    static CAguardaInspecao& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

private:
    CAguardaInspecao();

    static std::unique_ptr<CAguardaInspecao> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::IForm<api::IScreenMT>> m_form;
};

} // namespace vota
