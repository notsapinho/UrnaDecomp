#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CInspecionaUrna (RTTI: si_class of comum::CAppState; vtable @1547448 [244, 387, 11798, 7480, 1661, 218, 425,
// 11797, 425]): the urn's inspection starts; StartState logs it. It overrides the destructors, StartState (slot 2, fn
// 11798) and ProcessInput (slot 7, fn 11797). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors
// 49 final states share: a std::shared_ptr at +12 is all they release. +12 is the form: StartState shows it (slot 2
// of api::IForm) and ProcessInput reads it through api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read(), the
// voter screen's form: fn 11797 loads that Read()'s record (cinteractiveform.h:57 @1547504, `[MEDIA = api::IScreen,
// INPUT = api::IInputKbd]`), where the operator states' slots 7 load the <api::IScreenMT, api::IInputMT> one. The
// object is 20 bytes: vota::CAguardaMensagem::ProcessKey (fn 7481), the one caller of GetInst, holds it and the
// constructor inlined, allocates 20 bytes, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and builds +12
// through CTelasVota::GetTelaInspecionaUrna, and keeps the object in a static std::unique_ptr (@1837704) under a static
// std::mutex (@1837680), whose exit destructors are fns 11800 and 11799. ProcessInput goes, on CONFIRMA, to
// vota::CUrnaInspecionada's state, logs the confirmation and posts 11 to vota::CThreadOperador's queue.
// src/units/152-uenux2-app-vota-operador-estados.mk says which of this is chosen.
class CInspecionaUrna final : public comum::CAppState {
public:
    virtual ~CInspecionaUrna() override;

    static CInspecionaUrna& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CInspecionaUrna();

    static std::unique_ptr<CInspecionaUrna> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
