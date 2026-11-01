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

// vota::CDadoEleitorNaoConfere (RTTI: si_class of comum::CAppState; vtable @1592640 [448, 765, 10448, 7480, 1661, 218,
// 425, 10447, 425]): an operator's screen shown when the voter's datum does not match. It overrides StartState (slot
// 2, fn 10448), which shows the form at +20 when vota::CControlaReconhecimento's verifications reached their limit and
// the one at +12 otherwise, and ProcessInput (slot 7, fn 10447, pending: it calls fns 652 and 2735, which have no body
// here, and holds CControlaReconhecimento::AvancaVerificacao inlined, record ccontrolareconhecimento.cpp:176). The
// destructor is out of line, the body 19 final states share (fns 448 and 765): two std::shared_ptr, +20's released
// first. A singleton: fn 10443 (vota::CVerificaDadoEleitor::ProcessInput) holds GetInst and the constructor inlined,
// allocates 28 bytes and passes comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor; neither is
// reconstructed. src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is
// chosen.
class CDadoEleitorNaoConfere final : public comum::CAppState {
public:
    virtual ~CDadoEleitorNaoConfere() override;

    static CDadoEleitorNaoConfere& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDadoEleitorNaoConfere();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formLimite;
};

} // namespace vota
