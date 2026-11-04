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

// vota::CPerguntaEleitorVotando (RTTI: si_class of comum::CAppState; vtable @1593192 [244, 387, 10416, 7480, 1661,
// 218, 5394, 10415, 425]): the operator is asked whether the voter is voting; StartState logs it as an alert. It
// overrides the destructors, StartState (slot 2, fn 10416), ProcessKey (slot 6, fn 5394, one body with
// vota::CEleitorDemorando's slot 6) and ProcessInput (slot 7, fn 10415). Slots 0 and 1 are fns 244 and 387, the
// out-of-line destructors 49 final states share: a std::shared_ptr at +12 is all they release. +12 is the form:
// StartState shows it (slot 2 of api::IForm) and ProcessInput reads it through api::CInteractiveForm<api::IScreenMT,
// api::IInputMT>::Read() (record cinteractiveform.h:57 @1593248). A singleton: GetInst has no target function of its
// own, fn 10439 (vota::CEleitorDemorando::ProcessInput) holds it inlined (the one store of the vptr, 1593200), with the
// 20-byte object kept in a static std::unique_ptr (@1909372, destroyed at exit by fn 10418) under a static std::mutex
// (@1909348, by fn 10417); the constructor, inlined there behind a 64-byte frame of its own, passes
// comum::CAppState::EVENTO_TECLA | comum::CAppState::EVENTO_ENTRADA (3) to the base's.
// src/units/152-uenux2-app-vota-operador-estados.mk says which of this is chosen.
class CPerguntaEleitorVotando final : public comum::CAppState {
public:
    virtual ~CPerguntaEleitorVotando() override;

    static CPerguntaEleitorVotando& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

private:
    CPerguntaEleitorVotando();

    static std::unique_ptr<CPerguntaEleitorVotando> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
