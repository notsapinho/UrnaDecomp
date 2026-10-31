#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CQuerImprimirBU (RTTI: si_class of comum::CAppState; vtable @1542572 [244, 387, 12035, 7480, 1661, 218, 425,
// 12034, 425]): it overrides StartState (slot 2, fn 12035, records lines 40 and 41), which asserts that the vote is in
// EAVIMPRIMIRBU with no BU printed yet and shows the form, and ProcessInput (slot 7, fn 12034, pending: it calls fn
// 491, which has no body here). The destructors are the bodies the states over one std::shared_ptr at +12 share (fns
// 244 and 387): final, and out of line (docs/reference/facts/reading.md R4, R5). +12 is the form: StartState calls its
// slot 2, ProcessInput reads its input fields (+72) and focus (+84), CInteractiveForm's layout, with
// CPolySingleton<IInputKbd>'s instance (fn 455). GetInst, inlined into CInicioBU::StartState (fn 12062), builds the
// object over a member of CTelasVota::GetInst() (+236) that app/vota/eleitor/comum/ctelasvota.h has no accessor for: it
// and the statics are not reconstructed. Chosen: the member's name and the destructor declared first. This header's
// path is chosen, beside the .cpp the records name.
class CQuerImprimirBU final : public comum::CAppState {
public:
    virtual ~CQuerImprimirBU() override;

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
