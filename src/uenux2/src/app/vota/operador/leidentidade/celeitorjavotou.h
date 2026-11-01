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

// vota::CEleitorJaVotou (RTTI: si_class of comum::CAppState; vtable @1588804 [244, 387, 10642, 7480, 1661, 218, 425,
// 10641, 425]): an operator's screen. It overrides StartState (slot 2, fn 10642), which logs the alert through
// vota::CLogVota and shows the form at +12, and ProcessInput (slot 7, fn 10641, a thunk into binaryen's fn 6015, the
// body it shares with vota::CInformaAnoNascimentoErrado's), which goes to vota::CCancelaHabilitacaoEleitor on CONFIRMA.
// The destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it
// releases. A singleton: fn 10635 (vota::CEleitorEncontrado::StartState) holds GetInst and the constructor inlined,
// allocates 20 bytes and passes comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor; neither is
// reconstructed. src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is
// chosen.
class CEleitorJaVotou final : public comum::CAppState {
public:
    virtual ~CEleitorJaVotou() override;

    static CEleitorJaVotou& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEleitorJaVotou();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
