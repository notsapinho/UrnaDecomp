#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CRetirarMR (RTTI: si_class of comum::CAppState; vtable @1542676 [1284, 2884, 12031, 7480, 1661, 218, 425,
// 12030, 425]): it overrides StartState (slot 2, fn 12031, records lines 54 to 56, pending: it calls fn 491, which has
// no body here) and ProcessInput (slot 7, fn 12030, record line 78), which reads the form of the demo mode or the other
// one and goes to CEmitirMaisBU on CONFIRMA. The destructors are vota::CEleitorVotouNaoVotou's bodies (fns 1284 and
// 2884): the D2 releases three std::shared_ptr, at +12, +20 and +28, and stores no vptr, so the class is final, and the
// D0 calls it and frees `this`, so the destructor is out of line (docs/reference/facts/reading.md R4, R5). +12 is the
// form StartState shows (its slot 2); +20 and +28 are the forms ProcessInput reads (their input fields at +72 and focus
// at +84, CInteractiveForm's layout, with CPolySingleton<IInputKbd>'s instance), +28 when IInterfaceInit::GetDemoMode()
// is true. GetInst (fn 2291) is not reconstructed. Chosen: the members' names, +12's type (an IForm<IScreen>: only its
// slot 2 is called), and the destructor declared first. This header's path is chosen, beside the .cpp the records name.
class CRetirarMR final : public comum::CAppState {
public:
    virtual ~CRetirarMR() override;

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    std::shared_ptr<api::IForm<api::IScreen>> m_formRetirar;
    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_formDemo;
};

} // namespace vota
