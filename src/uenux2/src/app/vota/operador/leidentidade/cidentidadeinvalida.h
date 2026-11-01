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

// vota::CIdentidadeInvalida (RTTI: si_class of comum::CAppState; vtable @1588376 [244, 387, 10669, 7480, 1661, 218,
// 425, 10667, 425]): an operator's screen. It overrides StartState (slot 2, fn 10669), which logs the invalid
// identifier through vota::CLogVota and shows the form at +12, and ProcessInput (slot 7, fn 10667, pending: a thunk
// that passes INPUT_CORRIGE (5) to binaryen's fn 2295, whose next state is what fn 652, a GetInst with no body here,
// returns).
// The destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it
// releases. A singleton: fn 10627 (vota::CValidaIdentidade::StartState) holds GetInst and the constructor inlined,
// allocates 20 bytes and passes comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor; neither is
// reconstructed. src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is
// chosen.
class CIdentidadeInvalida final : public comum::CAppState {
public:
    virtual ~CIdentidadeInvalida() override;

    static CIdentidadeInvalida& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CIdentidadeInvalida();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
