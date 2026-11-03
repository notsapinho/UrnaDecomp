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

// vota::CEleitorImpedidoJustificarVotoCPF (RTTI: si_class of comum::CAppState; vtable @1589588 [244, 387, 1070, 7480,
// 1661, 218, 425, 10604, 425]): the operator's screen that says a justification cannot be made with the CPF. It
// overrides the destructors (fns 244 and 387, as vota::CPedeAnoNascimento's header says), StartState (slot 2, fn 1070,
// one body with the slot 2 of other states: it stays in the state, then shows the form at +12) and ProcessInput (slot
// 7, fn 10604: a thunk into binaryen's fn 2295 with api::INPUT_CORRIGE, which goes to CPedeIdentidade's state). A
// singleton: vota::IConfirmaJustificativa::ProcessInput (fn 10588), its one caller, holds GetInst and the constructor
// inlined, each behind a stack frame of its own; GetInst keeps the 20-byte object in a static std::unique_ptr
// (@1905868) under a static std::mutex (@1905844), whose exit destructors are fns 10606 and 10605. The constructor
// passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and builds the form straight into +12.
// src/units/283-uenux2-app-vota-operador-justificativa.mk says which of this is evidence and which is chosen.
class CEleitorImpedidoJustificarVotoCPF final : public comum::CAppState {
public:
    virtual ~CEleitorImpedidoJustificarVotoCPF() override;

    static CEleitorImpedidoJustificarVotoCPF& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEleitorImpedidoJustificarVotoCPF();

    static std::unique_ptr<CEleitorImpedidoJustificarVotoCPF> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
