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

// vota::CNomeEleitor (RTTI: si_class of comum::CAppState; vtable @1591248 [244, 387, 10501, 7480, 1661, 218, 425,
// 10500, 425]): the operator's screen with the voter's name, number, section and title. It overrides the destructors,
// StartState (slot 2, fn 10501) and ProcessInput (slot 7, fn 10500, records cnomeeleitor.cpp:145 and :156), both pending
// (src/units/239-uenux2-cnomeeleitor-pending.cpp says what each waits for). Slots 0 and 1 are fns 244 and 387, the
// out-of-line destructors the final states share: a std::shared_ptr at +12 is all they release. +12 is the form:
// StartState shows it. A singleton: GetInst (fn 5401) creates the 20-byte object under a static std::mutex (@1908816,
// destroyed at exit by fn 10502) and keeps it in a static std::unique_ptr (@1908840, by fn 10503); the constructor,
// inlined into it, initializes the form from a helper that builds it. The member names and the header's path (the
// class name in lower case, beside the records' cnomeeleitor.cpp) are chosen; src/units/239-uenux2-cnomeeleitor.mk says
// which of this is evidence.
class CNomeEleitor final : public comum::CAppState {
public:
    virtual ~CNomeEleitor() override;

    static CNomeEleitor& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CNomeEleitor();

    static std::unique_ptr<CNomeEleitor> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
