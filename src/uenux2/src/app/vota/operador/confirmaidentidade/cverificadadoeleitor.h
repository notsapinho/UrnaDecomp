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

// vota::CVerificaDadoEleitor (RTTI: si_class of comum::CAppState; vtable @1592712 [244, 387, 10444, 7480, 1661, 218,
// 425, 10443, 425]): an operator's screen that asks for a voter's personal datum for a manual habilitation. It
// overrides StartState (slot 2, fn 10444), which logs the request through vota::CLogVota and shows the form at +12, and
// ProcessInput (slot 7, fn 10443, pending: it calls fns 395, 652, 5396 and 5665, which have no body here). The
// destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it
// releases. A singleton: fn 2735 holds GetInst and the constructor inlined, allocates 20 bytes and passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor; neither is reconstructed.
// src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is chosen.
class CVerificaDadoEleitor final : public comum::CAppState {
public:
    virtual ~CVerificaDadoEleitor() override;

    static CVerificaDadoEleitor& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CVerificaDadoEleitor();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
