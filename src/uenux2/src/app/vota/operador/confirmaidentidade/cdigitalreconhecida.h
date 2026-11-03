#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CDigitalReconhecida (RTTI: si_class of comum::CAppState; vtable @1591640 [448, 765, 10482, 7480, 1661, 218,
// 425, 10481, 425]): the operator is told that the voter's fingerprint was recognized. It overrides the destructors,
// StartState (slot 2, fn 10482, record cdigitalreconhecida.cpp:47) and ProcessInput (slot 7, fn 10481, pending:
// src/units/282-uenux2-confirmaidentidade-estados-pending.cpp says what it waits for). The destructor is out of line:
// slots 0 and 1 are fns 448 and 765, the bodies the states with two std::shared_ptr at +12 and +20 share. A singleton:
// GetInst has no target function of its own, fn 5397 (vota::CPedeDigital::ObtemEstadoPosReconhecimentoBiometrico)
// holds it inlined (the one store of the vptr, 1591648), with the 28-byte object kept in a static std::unique_ptr
// (@1908980, destroyed at exit by fn 10484) under a static std::mutex (@1908956, by fn 10483). The constructor, inlined
// there behind a 16-byte frame of its own, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and fills the
// layout below; the form comes from a helper inlined there behind an 80-byte frame of its own (the fragment has it).
//
// The layout: +11 a byte the constructor copies from the election's parameters (CParametrosUrna's
// GetExibirScoreBiometria, the byte at +487 of comum::CConfiguracaoEleicao, which an offsetof of the tree's headers
// gives) and StartState compares with 1: when set, it formats the matcher's score (api::IFingerMatcher's slot 4) as
// "Score: {}" into +12's string; +12 a std::shared_ptr to that string, std::make_shared'd from " "; +20 the form, whose
// slot 2 StartState shows last. bool for the byte and every member name are chosen.
class CDigitalReconhecida final : public comum::CAppState {
public:
    virtual ~CDigitalReconhecida() override;

    static CDigitalReconhecida& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalReconhecida();

    static std::unique_ptr<CDigitalReconhecida> s_inst;
    static std::mutex s_mutex;

    bool m_bMostraScore;
    std::shared_ptr<std::string> m_score;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
