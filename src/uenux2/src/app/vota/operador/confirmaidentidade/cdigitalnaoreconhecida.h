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

// vota::CDigitalNaoReconhecida (RTTI: si_class of comum::CAppState; vtable @1591800 [1284, 2884, 10474, 7480, 1661,
// 218, 425, 10473, 425]): the operator is told that the voter's fingerprint was not recognized. It overrides the
// destructors, StartState (slot 2, fn 10474, record cdigitalnaoreconhecida.cpp:82, pending:
// src/units/282-uenux2-confirmaidentidade-estados-pending.cpp says what it waits for) and ProcessInput (slot 7, fn
// 10473). The destructor is out of line: slots 0 and 1 are fns 1284 and 2884, the bodies binaryen keeps once for the
// states with three std::shared_ptr at +12, +20 and +28 (vota::CRetirarMR's, CEleitorVotouNaoVotou's). A singleton:
// GetInst has no target function of its own, fn 5397 (vota::CPedeDigital::ObtemEstadoPosReconhecimentoBiometrico)
// holds it inlined (the one store of the vptr, 1591808), with the 36-byte object kept in a static std::unique_ptr
// (@1909036, destroyed at exit by fn 10476) under a static std::mutex (@1909012, by fn 10475). The constructor, inlined
// there behind a 112-byte frame of its own that holds the form's builder too, passes comum::CAppState::EVENTO_ENTRADA
// (2) to the base's and fills the layout below.
//
// The layout: +11 the byte vota::CDigitalReconhecida's constructor copies too (CParametrosUrna's
// GetExibirScoreBiometria, +487 of comum::CConfiguracaoEleicao); +12 and +20 two std::shared_ptr<std::string>, each
// std::make_shared'd (control block vptr 1588328, __shared_ptr_emplace<std::string>), the first from "Tentativa x de
// x", the second from " ", each the text of a field of the form; +28 the form, which ProcessInput reads through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1591872). bool for the
// byte and every member name are chosen; what StartState writes into the two strings is not read here.
class CDigitalNaoReconhecida final : public comum::CAppState {
public:
    virtual ~CDigitalNaoReconhecida() override;

    static CDigitalNaoReconhecida& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalNaoReconhecida();

    static std::unique_ptr<CDigitalNaoReconhecida> s_inst;
    static std::mutex s_mutex;

    bool m_bMostraScore;
    std::shared_ptr<std::string> m_tentativa;
    std::shared_ptr<std::string> m_score;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
