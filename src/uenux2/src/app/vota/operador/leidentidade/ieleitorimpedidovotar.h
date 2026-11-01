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

// vota::IEleitorImpedidoVotar (RTTI: si_class of comum::CAppState; vtable @1589136 [1257, 1689, 10625, 7480, 1661, 218,
// 425, 10624, 425, 218]): the base of the six states that tell the operator why a voter cannot vote
// (vota::CEleitorNaoEncontrado, CEleitorOptouPorVotarEmTransito, CEleitorImpedidoJustificar, CEleitorNaoTemIdadeMinima,
// CEleitorNaoPossuiCargosParaVotar, CEleitorImpedidoJustificarVotoTransito), whose vtables hold its StartState and
// ProcessInput and one pair of destructors (fns 1907 and 1689), and differ in slot 9 only, a slot the base adds with an
// empty body (fn 218); CEleitorNaoEncontrado alone overrides it. StartState (slot 2, fn 10625) shows the form at +12,
// calls slot 9, then fn 3616, and stays in the state; ProcessInput (slot 7, fn 10624) reads the form and goes to fn
// 652's state on INPUT_CONFIRMA (9) when the int at +20 is 0, and on INPUT_CORRIGE (5) when it is 1.
// Both are pending (src/units/161-uenux2-app-vota-operador-identidade-pending.cpp says what they wait for). The
// destructor is out of line: fn 1257 is a thunk into binaryen's fn 2902 with this class's vptr, and the derived
// classes' destructors call it (fn 1907, and fn 1689 frees after it). fn 1905 stores this class's vptr too; it is not
// reconstructed. src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is
// chosen.
class IEleitorImpedidoVotar : public comum::CAppState {
public:
    virtual ~IEleitorImpedidoVotar() override;

    virtual void StartState() override;

    virtual void ProcessInput() override;

    virtual void LogaImpedimento() {}

protected:
    IEleitorImpedidoVotar();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    int m_tipo;
};

} // namespace vota
