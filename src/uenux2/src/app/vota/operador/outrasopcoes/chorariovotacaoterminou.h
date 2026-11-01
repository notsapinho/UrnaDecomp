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

// vota::CHorarioVotacaoTerminou (RTTI: si_class of comum::CAppState; vtable @1586824 [244, 387, 10758, 7480, 1661,
// 218, 425, 10757, 425]): the voting hours are over; StartState logs it. It overrides the destructors, StartState
// (slot 2, fn 10758) and ProcessInput (slot 7, fn 10757), pending. Slots 0 and 1 are fns 244 and 387, the out-of-line
// destructors 49 final states share: a std::shared_ptr at +12 is all they release. +12 is the form: StartState shows
// it (slot 2 of api::IForm) and ProcessInput reads it through api::CInteractiveForm<api::IScreenMT,
// api::IInputMT>::Read(). The object's size and its other members are not recovered. GetInst and the constructor are
// not written: src/units/152-uenux2-app-vota-operador-estados.mk says what they wait for and which of this is chosen.
class CHorarioVotacaoTerminou final : public comum::CAppState {
public:
    virtual ~CHorarioVotacaoTerminou() override;

    static CHorarioVotacaoTerminou& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CHorarioVotacaoTerminou();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
