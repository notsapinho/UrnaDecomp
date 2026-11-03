#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CConfirmaInspecionada (RTTI: si_class of comum::CAppState; vtable @1590780 [244, 387, 1070, 7480, 1661, 218,
// 425, 10527, 425]): the operator confirms that the inspection of the urna is over. It overrides the destructors,
// StartState (slot 2, fn 1070, the body twelve states' slot 2 share, vota::CAguardaInspecao's among them: the next state
// is this, then the form's slot 2) and ProcessInput (slot 7, fn 10527). Slots 0 and 1 are fns 244
// and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at +12 is all they release, so the
// destructor is out of line (docs/reference/facts/reading.md R5) and the class final (R4). +12 is the form: StartState
// shows it and ProcessInput reads it through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record
// cinteractiveform.h:57). The object is 20 bytes. A singleton: GetInst and the constructor have no target index of
// their own: vota::CAguardaInspecao's slot 6 (fn 10530, its ProcessKey for key 11) holds both inlined, the one store of
// this class's vptr (1590788): the object made under a static std::mutex (@1908556) and kept in a static
// std::unique_ptr (@1908580), the constructor passing comum::CAppState::EVENTO_ENTRADA (2) to the base's and building
// the form from a helper, initialized in the member list (fn 301 writes into the member). They are written here, right
// by construction and compared with nothing (docs/how-to-decompile.md step 5), and nothing in the link calls them yet.
// src/units/281-uenux2-cconfirmainspecionada.mk says which of this is chosen.
class CConfirmaInspecionada final : public comum::CAppState {
public:
    virtual ~CConfirmaInspecionada() override;

    static CConfirmaInspecionada& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CConfirmaInspecionada();

    static std::unique_ptr<CConfirmaInspecionada> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
