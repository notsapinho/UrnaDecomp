#pragma once

#include <functional>
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

// vota::IEleitorImpedidoVotar (RTTI: si_class of comum::CAppState; vtable @1589136 [1257, 1689, 10625, 7480, 1661, 218,
// 425, 10624, 425, 218]): the base of the six states that tell the operator why a voter cannot vote
// (vota::CEleitorNaoEncontrado, CEleitorOptouPorVotarEmTransito, CEleitorImpedidoJustificar, CEleitorNaoTemIdadeMinima,
// CEleitorNaoPossuiCargosParaVotar, CEleitorImpedidoJustificarVotoTransito), whose vtables hold its StartState and
// ProcessInput and one pair of destructors (fns 1907 and 1689), and differ in slot 9 only, a slot the base adds with an
// empty body (fn 218); CEleitorNaoEncontrado alone overrides it. StartState (slot 2, fn 10625) shows the form at +12,
// calls slot 9, then fn 3616, and stays in the state; ProcessInput (slot 7, fn 10624) reads the form and goes to fn
// 652's state on INPUT_CONFIRMA (9) when the int at +20 is 0, and on INPUT_CORRIGE (5) when it is 1.
// Both are written; fn 3616 is vota::ApresentaFotoEleitor (app/vota/operador/comum/fotoeleitor.h). The
// destructor is out of line: fn 1257 is a thunk into binaryen's fn 2902 with this class's vptr, and the derived
// classes' destructors call it (fn 1907, and fn 1689 frees after it).
// The constructor is fn 1905, out of line (its callers are fn 5424, CEleitorNaoEncontrado::GetInst, and fn 10635, which
// calls it five times for the other derived classes): it passes comum::CAppState::EVENTO_ENTRADA (2) to the base's,
// stores its int at +20, and builds the form: the identity typed on line 1 (table slot 3907, GetTextoIdentidadeDigitada),
// the texts of its two std::function on lines 2 and 3 (api::CMTFormBuilderBase's AddTextField over a std::function, fn
// 5419, which takes a copy of each), and on line 4 "CONFIRMA: retornar" at the right when the int at +20 is 0 or
// "CORRIGE: retornar" at the left when it is 1, the key ProcessInput reads; the form is assigned to +12 in the body
// (the member is cleared first, then the result moved in). The derived classes pass two function pointers (the table
// slots of each __func<std::string (*)(), std::string ()> they build) and 0 or 1. src/units/161-uenux2-app-vota-
// operador-identidade.mk says which of this is evidence and which is chosen.
class IEleitorImpedidoVotar : public comum::CAppState {
public:
    virtual ~IEleitorImpedidoVotar() override;

    virtual void StartState() override;

    virtual void ProcessInput() override;

    virtual void LogaImpedimento() {}

protected:
    IEleitorImpedidoVotar(std::function<std::string()> linha2, std::function<std::string()> linha3, int tipo);

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    int m_tipo;
};

} // namespace vota
