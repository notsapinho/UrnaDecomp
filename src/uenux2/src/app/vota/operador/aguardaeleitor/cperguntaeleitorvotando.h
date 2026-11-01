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

// vota::CPerguntaEleitorVotando (RTTI: si_class of comum::CAppState; vtable @1593192 [244, 387, 10416, 7480, 1661,
// 218, 5394, 10415, 425]): the operator is asked whether the voter is voting; StartState logs it as an alert. It
// overrides the destructors, StartState (slot 2, fn 10416) and ProcessKey (slot 6, fn 5394), ProcessInput (slot 7, fn
// 10415), pending. Slots 0 and 1 are fns 244 and 387, the out-of-line destructors 49 final states share: a
// std::shared_ptr at +12 is all they release. +12 is the form: StartState shows it (slot 2 of api::IForm) and
// ProcessInput reads it through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read(). The object's size and
// its other members are not recovered. GetInst and the constructor are not written:
// src/units/152-uenux2-app-vota-operador-estados.mk says what they wait for and which of this is chosen.
class CPerguntaEleitorVotando final : public comum::CAppState {
public:
    virtual ~CPerguntaEleitorVotando() override;

    static CPerguntaEleitorVotando& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

private:
    CPerguntaEleitorVotando();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
