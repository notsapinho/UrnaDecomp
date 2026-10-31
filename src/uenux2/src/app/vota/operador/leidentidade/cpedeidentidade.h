#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IScreenMT;
class IInputMT;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPedeIdentidade (RTTI: si_class of comum::CAppState; vtable @1588232 [1537, 3629, 10680, 7480, 1661, 10678,
// 425, 10677, 10676]): the operator's screen that asks for the voter's identifier. It overrides StartState (slot 2,
// fn 10680, records cpedeidentidade.cpp:62 and :63), FinishState (slot 5, fn 10678), which stops the three ticks,
// ProcessInput (slot 7, fn 10677) and ProcessTick (slot 8, fn 10676); StartState, ProcessInput and ProcessTick are
// pending (src/units/161-uenux2-app-vota-operador-identidade-pending.cpp says what each waits for). The destructor is
// out of line, the body comum::CPedeDigitalMesario and vota::CRegistraDigitalOperador share (fns 1537 and 3629), which
// releases the std::shared_ptr at +24 and then the one at +16. The layout is what the slots and the destructor read:
// +11, +12 and +13 the three ticks StartState starts through vota::CThreadOperador (fn 700) and FinishState stops
// (fn 422), +16 a std::shared_ptr whose pointee no body here shows (chosen: the voter's form, as in
// comum::CPedeDigitalMesario), and +24 the form StartState shows and ProcessInput reads. A singleton: fn 652 holds
// GetInst and the constructor inlined; neither is reconstructed.
// src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is chosen.
class CPedeIdentidade final : public comum::CAppState {
public:
    virtual ~CPedeIdentidade() override;

    static CPedeIdentidade& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte id) override;

private:
    CPedeIdentidade();

    uebyte m_tickIdentidade;
    uebyte m_tickEspera;
    uebyte m_tickAviso;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
