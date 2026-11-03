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

// vota::CPedeAnoNascimento (RTTI: si_class of comum::CAppState; vtable @1589876 [244, 387, 1718, 7480, 1661, 218, 425,
// 10590, 425]): the operator's screen that asks for the voter's year of birth on the way to a justification. It
// overrides the destructors, StartState (slot 2, fn 1718, one body with the slot 2 of other states: it shows the form
// at +12 and stays) and ProcessInput (slot 7, fn 10590, pending: src/units/283-uenux2-app-vota-operador-justificativa-
// pending.cpp says what it waits for). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors of the final
// states whose one member is a std::shared_ptr at +12 (244 stores no vptr, docs/reference/facts/reading.md R4; 387 is
// `f244(p0); f136(p0)`, R5). A singleton: GetInst (fn 5418) creates the 20-byte object on first use and keeps it in a
// static std::unique_ptr (@1905980) under a static std::mutex (@1905956), whose exit destructors are fns 10592 and
// 10591; the constructor, inlined there behind its own stack frame, passes comum::CAppState::EVENTO_ENTRADA (2) to the
// base's and builds the form straight into +12. GetInst's callers are vota::IConfirmaJustificativa::ProcessInput (fn
// 10588) and fn 6014, the body binaryen merged from CEleitorMenor16Anos's and CAnoInformadoInvalido's ProcessInput.
// src/units/283-uenux2-app-vota-operador-justificativa.mk says which of this is evidence and which is chosen.
class CPedeAnoNascimento final : public comum::CAppState {
public:
    virtual ~CPedeAnoNascimento() override;

    static CPedeAnoNascimento& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CPedeAnoNascimento();

    static std::unique_ptr<CPedeAnoNascimento> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
