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
// measurement) and ProcessInput (slot 7, fn 10489). A singleton: fn 10500 creates the 36-byte object on first
// use and keeps it in a static std::unique_ptr (@1908924) under a static std::mutex (@1908900), destroyed at exit by fns
// 10492 and 10491; the constructor, inlined there, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and stores
// what the layout below holds. The destructor is out of line: the deleting one (fn 765) calls it and frees `this`, and
// it stores no vptr, as a final class's; 19 states share the two bodies, fns 448 and 765. Not recovered: the constructor
// and GetInst (fn 10500, which holds them inlined, calls fn 1151, vota::AdicionaCampoNumerico, and six with no name).
//
// The layout: +12 and +20 two forms, each from api::CMTFormBuilder::GetInteractiveForm (fn 301); StartState shows the
// first. +28 a 32-bit word that the constructor and StartState set to 0 and ProcessInput counts up, comparing it with 1
// unsigned (`i32.le_u`, measured: an int gives `i32.le_s` with 0), and +32 a byte both set to 1. unsigned int's
// spelling and bool, the plainest type of that width, are a choice, and so are the member names.
//
// ProcessInput (fn 10489): while +32 is set it holds the reading of the first form behind a 16-byte frame of its own
// (binaryen's inlining of a function out of line here, a reading: the second form's Read uses ProcessInput's own frame),
// LeAnoDigitado: on CONFIRMA the first entry's text, when it has four characters or more, through std::stoul (fn 4661)
// against md::CEleitorDecorator::GetAnoNascimento (fn 5665) of the current voter, logged both ways after
// CLogVota::GetInst; equal goes to CInformaEleitorPodeVotar (fn 5399), different adds one to +28 and shows the second
// form the first time, with +32 cleared, and goes to CInformaAnoNascimentoErrado after; CORRIGE logs
// LogaHabilitacaoCanceladaConfirmacaoDado (fn 2097) and goes to CCancelaHabilitacaoEleitor (fn 1536). With +32 clear,
// CONFIRMA on the second form sets it again and shows the first. LeAnoDigitado's name, its being a private member and
// the local's name are chosen.
class CPedeAnoNascimentoSemBiometria final : public comum::CAppState {
public:
    virtual ~CPedeAnoNascimentoSemBiometria() override;

    static CPedeAnoNascimentoSemBiometria& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CPedeAnoNascimentoSemBiometria();

    void LeAnoDigitado();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formErro;
    unsigned int m_tentativas;
    bool m_bPrimeira;
};

} // namespace vota
