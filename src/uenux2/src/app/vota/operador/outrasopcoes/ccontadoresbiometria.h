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

// vota::CContadoresBiometria (RTTI: si_class of comum::CAppState; vtable @1587924 [244, 387, 1070, 7480, 1661, 218,
// 425, 10698, 425]): the screen of the biometric counters. It overrides the destructors, StartState (slot 2, fn 1070,
// the body it shares with comum::CDigitalMesarioNaoReconhecida's and other states' StartState) and ProcessInput (slot
// 7, fn 10698, which goes back to vota::CEscolheOpcao on api::INPUT_CORRIGE, reading the form through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read(), record cinteractiveform.h:57 @1587980). Slots 0 and 1
// are fns 244 and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at +12, the form, is all
// they release. A singleton: GetInst creates the 20-byte object under a static std::mutex (@1905256) and keeps it in a
// static std::unique_ptr (@1905280). Its one caller, vota::CEscolheOpcao's ConfirmaOpcao (inlined into fn 10689),
// holds it inlined with the constructor behind a 64-byte frame of its own, so it has no target function: written in
// ccontadoresbiometria.cpp, it has that one call site in our link too. The constructor builds the form from three
// texts passed by table slot (fns 10701, 10700 and 10699, defined there), right-aligned at column 35 of lines 1 to 3,
// "CORRIGE: retornar" and the input control. The member names are chosen.
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CContadoresBiometria final : public comum::CAppState {
public:
    virtual ~CContadoresBiometria() override;

    static CContadoresBiometria& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CContadoresBiometria();

    static std::unique_ptr<CContadoresBiometria> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
