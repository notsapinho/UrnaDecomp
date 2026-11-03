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

// vota::CDesabilitaAudioEleitor (RTTI: si_class of comum::CAppState; vtable @1592856 [244, 387, 10436, 7480, 1661,
// 218, 425, 10435, 425]): the operator is asked to unplug the voter's headphones; StartState logs it. It overrides
// the destructors, StartState (slot 2, fn 10436) and ProcessInput (slot 7, fn 10435). Slots 0 and 1 are fns
// 244 and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at +12 is all they release. +12
// is the form: StartState shows it (slot 2 of api::IForm) and ProcessInput reads it through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read(). The object's size and its other members are not
// recovered. A singleton: GetInst (fn 5393) creates the object under a static std::mutex (@1909236, destroyed at exit
// by fn 10437) and keeps it in a static std::unique_ptr (@1909260, by fn 10438); the constructor, inlined into it,
// initializes the form from a helper that builds it. src/units/152-uenux2-app-vota-operador-estados.mk says which of
// this is chosen.
class CDesabilitaAudioEleitor final : public comum::CAppState {
public:
    virtual ~CDesabilitaAudioEleitor() override;

    static CDesabilitaAudioEleitor& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDesabilitaAudioEleitor();

    static std::unique_ptr<CDesabilitaAudioEleitor> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
