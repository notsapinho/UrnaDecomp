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

// vota::CDigitalNaoReconhecidaDecBiometria (RTTI: si_class of comum::CAppState; vtable @1591728 [244, 387, 10478, 7480,
// 1661, 218, 425, 10477, 425]): an operator's screen of the voter's fingerprint not recognized. It overrides the
// destructors, StartState (slot 2, fn 10478, pending: src/units/282-uenux2-confirmaidentidade-estados-pending.cpp says
// what it waits for) and ProcessInput (slot 7, fn 10477). The destructor is out of line, the body 49 final states share
// (fns 244 and 387): a std::shared_ptr at +12 is all it releases. A singleton: fn 10474
// (vota::CDigitalNaoReconhecida::StartState, pending) holds GetInst and the constructor inlined (the one store of the
// vptr, 1591736): a 20-byte object, comum::CAppState::EVENTO_ENTRADA (2) passed to the base's constructor, the form at
// +12. GetInst and the constructor are declared only: they wait for 10474. +12 is the form ProcessInput reads through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1591784). The member's
// name is chosen.
class CDigitalNaoReconhecidaDecBiometria final : public comum::CAppState {
public:
    virtual ~CDigitalNaoReconhecidaDecBiometria() override;

    static CDigitalNaoReconhecidaDecBiometria& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalNaoReconhecidaDecBiometria();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
