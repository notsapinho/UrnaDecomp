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

// vota::CDigitalNaoReconhecidaPorTempo (RTTI: si_class of comum::CAppState; vtable @1591568 [448, 765, 10486, 7480,
// 1661, 218, 425, 10485, 425]): an operator's screen of the voter's fingerprint not recognized in time. It overrides
// the destructors, StartState (slot 2, fn 10486) and ProcessInput (slot 7, fn 10485). The destructor is out of line, the body 19 final states
// share (fns 448 and 765): two std::shared_ptr, +20's released first. A singleton: fn 10465
// (vota::CPedeDigital::ProcessTick, pending) holds GetInst and the constructor inlined (the one store of the vptr,
// 1591576): a 28-byte object, comum::CAppState::EVENTO_ENTRADA (2) passed to the base's constructor, +12 a
// std::shared_ptr<std::string> std::make_shared'd from "Tentativa x de x" (control block vptr 1588328), +20 the form.
// GetInst and the constructor are declared only: they wait for 10465. ProcessInput reads +20 through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1591624). The member
// names are chosen.
class CDigitalNaoReconhecidaPorTempo final : public comum::CAppState {
public:
    virtual ~CDigitalNaoReconhecidaPorTempo() override;

    static CDigitalNaoReconhecidaPorTempo& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalNaoReconhecidaPorTempo();

    std::shared_ptr<std::string> m_tentativa;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
