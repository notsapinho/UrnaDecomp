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

// vota::CVerificaDadoEleitor (RTTI: si_class of comum::CAppState; vtable @1592712 [244, 387, 10444, 7480, 1661, 218,
// 425, 10443, 425]): an operator's screen that asks for a voter's personal datum for a manual habilitation. It
// overrides StartState (slot 2, fn 10444), which logs the request through vota::CLogVota and shows the form at +12, and
// ProcessInput (slot 7, fn 10443), which on CONFIRMA compares the year typed, when it has four characters or more,
// with md::CEleitorDecorator::GetAnoNascimento (fn 5665) of the current voter and goes to CRegistraDigitalOperador (fn
// 5396) or CDadoEleitorNaoConfere (whose GetInst it holds inlined), and on CORRIGE to CPedeIdentidade (fn 652). The
// destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12
// is all it releases. A singleton: GetInst (fn 2735) creates the 20-byte object under a static std::mutex (@1909180,
// destroyed at exit by fn 10445) and keeps it in a static std::unique_ptr (@1909204, by fn 10446, a thunk into
// binaryen's fn 389); the constructor, inlined there, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and
// builds the form at +12 behind a 96-byte frame. src/units/161-uenux2-app-vota-operador-identidade.mk has the form and
// says which of this is evidence and which is chosen.
class CVerificaDadoEleitor final : public comum::CAppState {
public:
    virtual ~CVerificaDadoEleitor() override;

    static CVerificaDadoEleitor& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CVerificaDadoEleitor();

    static std::unique_ptr<CVerificaDadoEleitor> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
