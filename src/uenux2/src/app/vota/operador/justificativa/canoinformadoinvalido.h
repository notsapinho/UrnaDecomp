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

// vota::CAnoInformadoInvalido (RTTI: si_class of comum::CAppState; vtable @1589660 [244, 387, 1070, 7480, 1661, 218,
// 425, 10601, 425]): the operator's screen that says the year of birth typed is not valid. It overrides the destructors
// (fns 244 and 387, as vota::CPedeAnoNascimento's header says), StartState (slot 2, fn 1070, one body with the slot 2
// of other states) and ProcessInput (slot 7, fn 10601), which goes back to vota::CPedeAnoNascimento on
// api::INPUT_CONFIRMA: 10601 is `f6014(p0, 1589716)`, a thunk into the body binaryen merged from this class's and
// vota::CEleitorMenor16Anos's ProcessInput, which differ in the address of their TU's copy of the record of
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (cinteractiveform.h:57, here @1589716). A singleton:
// CPedeAnoNascimento::ProcessInput (fn 10590), its one caller, holds GetInst and the constructor inlined;
// GetInst keeps the 20-byte object in a static std::unique_ptr (@1905896) under a static std::mutex (@1905872), whose
// exit destructors are fns 10603 and 10602. The constructor passes comum::CAppState::EVENTO_ENTRADA (2) to the base's
// and builds the form straight into +12. src/units/283-uenux2-app-vota-operador-justificativa.mk says which of this is
// evidence and which is chosen.
class CAnoInformadoInvalido final : public comum::CAppState {
public:
    virtual ~CAnoInformadoInvalido() override;

    static CAnoInformadoInvalido& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CAnoInformadoInvalido();

    static std::unique_ptr<CAnoInformadoInvalido> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
