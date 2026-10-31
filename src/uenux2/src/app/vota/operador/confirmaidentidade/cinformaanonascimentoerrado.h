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

// vota::CInformaAnoNascimentoErrado (RTTI: si_class of comum::CAppState; vtable @1591424 [244, 387, 1070, 7480, 1661,
// 218, 425, 10493, 425]): an operator's screen. It overrides StartState (slot 2, fn 1070, one body in twelve states'
// slot 2: it shows the form at +12) and ProcessInput (slot 7, fn 10493, a thunk into binaryen's fn 6015, the body it
// shares with vota::CEleitorJaVotou's), which goes to vota::CCancelaHabilitacaoEleitor on CONFIRMA. The destructor is
// out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it releases. A
// singleton: fn 10489 (vota::CPedeAnoNascimentoSemBiometria::ProcessInput) holds GetInst and the constructor inlined,
// allocates 20 bytes and passes comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor; neither is
// reconstructed. src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is
// chosen.
class CInformaAnoNascimentoErrado final : public comum::CAppState {
public:
    virtual ~CInformaAnoNascimentoErrado() override;

    static CInformaAnoNascimentoErrado& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CInformaAnoNascimentoErrado();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
