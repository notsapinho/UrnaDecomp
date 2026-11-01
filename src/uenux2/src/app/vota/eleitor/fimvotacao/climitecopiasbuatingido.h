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

// vota::CLimiteCopiasBUAtingido (RTTI: si_class of comum::CAppState; vtable @1542828 [244, 387, 12027, 7480, 1661, 218,
// 425, 12026, 425]): it overrides StartState (slot 2, fn 12027, record line 37), which asserts that the vote is
// EAVENCERRADA, logs through CLogVota (fn 4556) and shows the form, and ProcessInput (slot 7, fn 12026), which goes to
// CMostraQRCodeBU on CONFIRMA. The destructors are the bodies the states over one std::shared_ptr at +12 share (fns 244
// and 387, vota::CMaisInformacoes's symbols): the D2 stores no vptr, so the class is final, and the D0 calls it and
// frees `this`, so the destructor is out of line (docs/reference/facts/reading.md R4, R5). +12 is the form: StartState
// calls its slot 2, ProcessInput reads its input fields (+72) and focus (+84), CInteractiveForm's layout, with
// CPolySingleton<IInputKbd>'s instance (fn 455), the Read() of a CFormInterativoTelaVota. A singleton: GetInst, inlined
// into CVerificaQtdBUsAdicionais::StartState (fn 12023), keeps the object in a static std::unique_ptr (@1833960,
// destroyed at exit by fn 12029) under a static std::mutex (@1833936, by fn 12028), and builds it as the base's
// constructor with 2 and, at +12, a copy of CTelasVota::GetInst()'s member at +108. Chosen: the member's name, the names
// GetInst, s_inst and s_mutex, and the destructor declared first. This header's path is chosen, beside the .cpp the
// record names.
class CLimiteCopiasBUAtingido final : public comum::CAppState {
public:
    virtual ~CLimiteCopiasBUAtingido() override;

    static CLimiteCopiasBUAtingido& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CLimiteCopiasBUAtingido();

    static std::mutex s_mutex;
    static std::unique_ptr<CLimiteCopiasBUAtingido> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
