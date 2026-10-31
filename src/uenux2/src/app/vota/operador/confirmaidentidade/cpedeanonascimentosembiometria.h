#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPedeAnoNascimentoSemBiometria (RTTI: si_class of comum::CAppState; vtable @1591496 [448, 765, 10490, 7480,
// 1661, 218, 425, 10489, 425]): an operator's screen; ProcessInput's messages compare the year of birth typed with the
// register's. It overrides the destructors, StartState (slot 2, fn 10490, written, `differs`: fragment 142 has the
// measurement) and ProcessInput (slot 7, fn 10489, pending). A singleton: fn 10500 creates the 36-byte object on first
// use and keeps it in a static std::unique_ptr (@1908924) under a static std::mutex (@1908900), destroyed at exit by fns
// 10492 and 10491; the constructor, inlined there, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and stores
// what the layout below holds. The destructor is out of line: the deleting one (fn 765) calls it and frees `this`, and
// it stores no vptr, as a final class's; 19 states share the two bodies, fns 448 and 765. Not recovered: the constructor
// and GetInst (fn 10500, which holds them inlined, calls fns 395, 1151 and eight others that have no name).
//
// The layout: +12 and +20 two forms, each from api::CMTFormBuilder::GetInteractiveForm (fn 301); StartState shows the
// first. +28 a 32-bit word that the constructor and StartState set to 0, and +32 a byte both set to 1. int and bool are
// the plainest types of those widths, a choice, and so are the member names.
class CPedeAnoNascimentoSemBiometria final : public comum::CAppState {
public:
    virtual ~CPedeAnoNascimentoSemBiometria() override;

    static CPedeAnoNascimentoSemBiometria& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CPedeAnoNascimentoSemBiometria();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formErro;
    int m_tentativas;
    bool m_bPrimeira;
};

} // namespace vota
