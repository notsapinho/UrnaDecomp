#pragma once

#include <memory>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::IConfirmaJustificativa (RTTI: si_class of comum::CAppState; vtable @1589948 [1688, 2748, 10589, 7480, 1661, 218,
// 425, 10588, 425]), the base of vota::CConfirmaJustificativa, CConfirmaJustificativaTemporario and
// CConfirmaJustificativaTransito, whose vtables hold the same slots but slot 0 (fn 3626, a call of fn 1688). It overrides
// StartState (slot 2, fn 10589) and ProcessInput (slot 7, fn 10588), both pending (unit 174's -pending.cpp says what
// they wait for). The constructor (fn 3625, record iconfirmajustificativa.cpp:34, which spells its parameter) passes 2 to
// the base's and builds, with api::CMTFormBuilder::GetInteractiveForm (fn 301), the std::shared_ptr it moves into +12;
// it is not written (it calls fn 395, which has no name). The destructor is out of line: fn 1688 is a thunk into
// binaryen's fn 2902 with this class's vptr, a body the target forms from four such thunks (vota::IEleitorImpedidoVotar's
// 1257 among them), and the deleting destructor (fn 2748) calls it and frees `this` after a drop. The member's name, and
// its pointee's type (vota::IEleitorImpedidoVotar's form, what GetInteractiveForm returns), are chosen.
class IConfirmaJustificativa : public comum::CAppState {
public:
    explicit IConfirmaJustificativa(const std::string& justificativa);

    virtual ~IConfirmaJustificativa() override;

    virtual void StartState() override;

    virtual void ProcessInput() override;

protected:
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
