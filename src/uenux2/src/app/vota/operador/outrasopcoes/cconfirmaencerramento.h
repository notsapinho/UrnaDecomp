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

// vota::CConfirmaEncerramento (RTTI: si_class of comum::CAppState; vtable @1587268 [244, 387, 1718, 7480, 1661, 218,
// 425, 10734, 425]): the operator confirms closing the voting. It overrides the destructors, StartState (slot 2, fn
// 1718, the body it shares with vota::CUrnaInspecionada's and other states' StartState) and ProcessInput (slot 7, fn
// 10734). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at
// +12, the form, is all they release. A singleton: GetInst (fn 3632) creates the 20-byte object under a static
// std::mutex (@1905032) and keeps it in a static std::unique_ptr (@1905056); the constructor, inlined there, passes
// EVENTO_ENTRADA (2) to the base's and initializes the form from a helper that builds it. The member names are chosen.
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CConfirmaEncerramento final : public comum::CAppState {
public:
    virtual ~CConfirmaEncerramento() override;

    static CConfirmaEncerramento& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CConfirmaEncerramento();

    static std::unique_ptr<CConfirmaEncerramento> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
