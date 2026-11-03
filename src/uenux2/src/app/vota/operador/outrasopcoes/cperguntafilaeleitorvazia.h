#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPerguntaFilaEleitorVazia (RTTI: si_class of comum::CAppState; vtable @1587692 [244, 387, 10715, 7480, 1661,
// 218, 425, 10713, 425]): the operator is asked whether everyone present has voted; StartState logs it. It overrides
// the destructors, StartState (slot 2, fn 10715) and ProcessInput (slot 7, fn 10713: vota::CPedeTituloEncerramento on
// api::INPUT_CONFIRMA, vota::CAguardaEleitoresVotarem on api::INPUT_CORRIGE, each logged). Slots 0 and 1 are fns 244
// and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at +12 is all they release. +12 is the
// form: StartState shows it (slot 2 of api::IForm) and ProcessInput reads it through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1587748). A singleton:
// GetInst (fn 5426) creates the 20-byte object under a static std::mutex (@1905172) and keeps it in a static
// std::unique_ptr (@1905196); the constructor, inlined there, passes EVENTO_ENTRADA (2) to the base's and initializes
// the form from a helper that builds it. src/units/152-uenux2-app-vota-operador-estados.mk says which of this is chosen.
class CPerguntaFilaEleitorVazia final : public comum::CAppState {
public:
    virtual ~CPerguntaFilaEleitorVazia() override;

    static CPerguntaFilaEleitorVazia& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CPerguntaFilaEleitorVazia();

    static std::unique_ptr<CPerguntaFilaEleitorVazia> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
