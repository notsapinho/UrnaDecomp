#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CIdentidadeInvalida (RTTI: si_class of comum::CAppState; vtable @1588376 [244, 387, 10669, 7480, 1661, 218,
// 425, 10667, 425]): an operator's screen. It overrides StartState (slot 2, fn 10669), which logs the invalid
// identifier through vota::CLogVota and shows the form at +12, and ProcessInput (slot 7, fn 10667: a thunk that passes
// INPUT_CORRIGE (5) to binaryen's fn 2295, whose next state is what fn 652, CPedeIdentidade::GetInst, returns;
// src/units/161-uenux2-app-vota-operador-identidade.mk has what it was measured with).
// The destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it
// releases. A singleton: fn 10627 (vota::CValidaIdentidade::StartState) holds GetInst and the constructor inlined, the
// one store of the vptr (1588384): the 20-byte object made under a static std::mutex (@1905340, destroyed at exit by fn
// 10671) and kept in a static std::unique_ptr (@1905364, by fn 10672), the constructor passing
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and building the form at +12 from a helper, initialized in the
// member list (fn 301 writes into the member). The form shows the identifier typed through TextoIdentidadeInvalida
// (fn 10670, below). src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is
// chosen.
class CIdentidadeInvalida final : public comum::CAppState {
public:
    virtual ~CIdentidadeInvalida() override;

    static CIdentidadeInvalida& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CIdentidadeInvalida();

    static std::unique_ptr<CIdentidadeInvalida> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// The text of the form's second field, passed by its table slot (3860) to api::CMTFormBuilder::AddTextField (fn 619):
// fn 10670, `f3623(p0)`, the identifier typed (vota::GetIdentidadeDigitada, fn 3623). Its band puts it after the
// statics' exit destructors and before StartState (fn 10669), so it is external, defined there. Its name and its being a
// free function of vota are chosen.
std::string TextoIdentidadeInvalida();

} // namespace vota
