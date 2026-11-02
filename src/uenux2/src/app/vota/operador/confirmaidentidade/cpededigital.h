#pragma once

#include <memory>

#include "api/gui/capplicationcontext.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPedeDigital (RTTI: si_class of comum::CAppState; vtable @1591888 [2739, 10469, 10468, 7480, 1661, 10467, 425,
// 10466, 10465]): the operator's screen that reads the voter's fingerprint. It overrides the destructors (slots 0 and 1,
// fns 2739 and 10469), StartState (slot 2, fn 10468, records cpededigital.cpp:115, 120 and 125), FinishState (slot 5,
// fn 10467, records 131 and 132), ProcessInput (slot 7, fn 10466) and ProcessTick (slot 8, fn 10465, records 162 to
// 164); StartState, FinishState and ProcessTick are pending (src/units/192-uenux2-app-vota-estados-sincronismo-pending.cpp
// says what each waits for). A singleton: fn 2740 creates the 84-byte object on first use and keeps it in a static
// std::unique_ptr (@1909064); the constructor, inlined there, passes comum::CAppState::EVENTO_ENTRADA |
// comum::CAppState::EVENTO_TICK (6) to the base's and stores what the layout below holds. Not recovered: the
// constructor, GetInst (fn 2740, which calls fns 395, 1151 and others that have no name) and the members the records
// name at lines 234, 262 and 279 (ObtemEstadoPosReconhecimentoBiometrico, VerificaDigital, VerificaDigitalTreinamento).
//
// The destructor is out of line: the deleting one (fn 10469) calls it, drops its result and frees `this`
// (docs/how-to-decompile.md step 5). It destroys, in this order, the api::CApplicationContext at +32 (a call of its
// destructor, fn 1468), then the std::shared_ptr at +24 and the one at +16, and stores no vptr first: a final class.
//
// The layout: +11, +12 and +13 three bytes, each the id vota::CThreadVota::AddStoppedTick (fn 807) returns on
// vota::CThreadOperador for 30000, 15000 and 50 ms, the first in the base's tail padding; +16 and +24 two forms, each
// from api::CMTFormBuilder::GetInteractiveForm (fn 301), and ProcessInput reads the first; +32 the context
// api::CriaContextoAplicacao (fn 3682) builds with the kind 2. The member names are chosen; the bytes' type is the type
// of AddStoppedTick's result.
class CPedeDigital final : public comum::CAppState {
public:
    virtual ~CPedeDigital() override;

    static CPedeDigital& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte tick) override;

private:
    CPedeDigital();

    uebyte m_tickLeitura;
    uebyte m_tickTimeout;
    uebyte m_tickVerificacao;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formErro;
    api::CApplicationContext m_contexto;
};

} // namespace vota
