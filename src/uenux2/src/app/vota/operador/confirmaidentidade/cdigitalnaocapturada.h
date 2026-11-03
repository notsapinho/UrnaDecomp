#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CDigitalNaoCapturada (RTTI: si_class of comum::CAppState; vtable @1592352 [244, 387, 1070, 7480, 1661, 218,
// 425, 10458, 425]): the screen vota::CRegistraDigitalOperador::ProcessTick (fn 10451) shows when the capture tick
// (+11) expires and the byte at +32 of that class, decremented, is not yet 0: "Digital não capturada" and "CONFIRMA:
// tentar novamente". It overrides StartState (slot 2, fn 1070, one body in
// twelve states' slot 2: it shows the form at +12) and ProcessInput (slot 7, fn 10458), which goes back to
// vota::CRegistraDigitalOperador on CONFIRMA. The destructor is out of line, the body 49 final states share (fns 244
// and 387): a std::shared_ptr at +12 is all it releases. A singleton: vota::CRegistraDigitalOperador::ProcessTick (fn
// 10451, not written) holds GetInst and the constructor inlined, allocates 20 bytes, passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor and builds the form behind a frame of its own; the
// statics are @1909120 (the std::unique_ptr) and @1909096 (the std::mutex), whose exit destructors are fns 10460 and
// 10459. Neither GetInst nor the constructor is reconstructed, nor are the statics. The file is named after the class,
// in the directory of the objects around its vtable, a choice (src/units/278-uenux2-cvalidaidentidade.mk says
// why).
class CDigitalNaoCapturada final : public comum::CAppState {
public:
    virtual ~CDigitalNaoCapturada() override;

    static CDigitalNaoCapturada& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalNaoCapturada();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
