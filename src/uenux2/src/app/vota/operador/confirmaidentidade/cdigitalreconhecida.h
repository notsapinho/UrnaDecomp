#pragma once

#include <memory>
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
// slots 0 and 1 are fns 448 and 765, the bodies the states with two std::shared_ptr at +12 and +20 share. GetInst and
// the constructor have no target function of their own: fn 5397 holds them inlined (the one store of the vptr, 1591648)
// and is not reconstructed, so they are declared only.
//
// The layout, from StartState: +11 a byte it compares with 1 and, when set, formats the matcher's score
// (api::IFingerMatcher's slot 4) as "Score: {}" into +12's string; +12 a std::shared_ptr to that string; +20 the form,
// whose slot 2 it shows last. bool for the byte and every member name are chosen.
class CDigitalReconhecida final : public comum::CAppState {
public:
    virtual ~CDigitalReconhecida() override;

    static CDigitalReconhecida& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalReconhecida();

    bool m_bMostraScore;
    std::shared_ptr<std::string> m_score;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
