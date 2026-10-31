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

// vota::CImprimindoBU (RTTI: si_class of comum::CAppState; vtable @1541292 [244, 387, 12078, 7480, 1661, 218, 425,
// 12077, 425]): it overrides StartState (slot 2, fn 12078, records lines 70 and 71) and ProcessInput (slot 7, fn
// 12077), both pending: StartState calls fns 1127 and 4551 and ImprimeBU (fn 2890, records lines 111 and 114),
// ProcessInput fns 491 and 3701, none with a body here. The destructors are the bodies the states over one
// std::shared_ptr at +12 share (fns 244 and 387): final, and out of line (docs/reference/facts/reading.md R4, R5). A
// singleton: GetInst (fn 5986) keeps the object in a static std::unique_ptr (@1833652, destroyed at exit by fn 12080)
// under a static std::mutex (@1833628, by fn 12079), and builds it as the base's constructor with 2 and, at +12, a copy
// of CTelasVota::GetInst()'s member at +100, the form. Chosen: the member's name and its type (CTelasVota's members'
// type, which ctelasvota.h chooses), the names GetInst, s_inst and s_mutex, the destructor declared first. This
// header's path is chosen, beside the .cpp the records name.
class CImprimindoBU final : public comum::CAppState {
public:
    virtual ~CImprimindoBU() override;

    static CImprimindoBU& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CImprimindoBU();

    static std::mutex s_mutex;
    static std::unique_ptr<CImprimindoBU> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
