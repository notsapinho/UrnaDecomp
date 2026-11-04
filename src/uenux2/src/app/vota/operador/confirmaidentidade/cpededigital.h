#pragma once

#include <memory>
#include <mutex>
#include <utility>

#include "api/gui/capplicationcontext.h"
#include "api/hwil/ifingerscanner.h"
#include "app/comum/cappstate.h"

namespace comum {
// The score of a fingerprint's comparison: the name is the records' (cpededigital.cpp:262 and :279 print
// `std::pair<bool, comum::TScoreHabilitacao>`), and fn 10465 stores it with i32.store16 where it keeps the pair; that
// it is ueword, the alias and its place here, beside the class whose records name it, are chosen.
using TScoreHabilitacao = ueword;
} // namespace comum

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
// 164). A
// singleton: GetInst (fn 2740) creates the 84-byte object on first use under a static std::mutex (@1909040, destroyed
// at exit by fn 10471) and keeps it in a static std::unique_ptr (@1909064, by fn 10472); the constructor, inlined
// there behind a frame of its own, passes comum::CAppState::EVENTO_ENTRADA | comum::CAppState::EVENTO_TICK (6) to the
// base's and stores what the layout below holds. ObtemEstadoPosReconhecimentoBiometrico is the member its record names
// (cpededigital.cpp:234, fn 5397), out of line with two calls from ProcessTick; the members the records name at lines
// 262 and 279 (VerificaDigital, VerificaDigitalTreinamento, each the column of its CPolySingleton<IFingerMatcher>
// instance call) are held inlined by ProcessTick, each behind a frame of its own (32 and 16 bytes): binaryen inlined
// them into their one caller, so they are out of line here, with no index of their own. PararTicks, the three ticks'
// StopTick, which ProcessTick's timeout path, VerificaDigital and VerificaDigitalTreinamento call, has no record or
// index: clang inlines it into the three (wasm-ld drops the copy it emits); that it is a member, its name and its line
// are chosen.
//
// The destructor is out of line: the deleting one (fn 10469) calls it, drops its result and frees `this`
// (docs/how-to-decompile.md step 5). It destroys, in this order, the api::CApplicationContext at +32 (a call of its
// destructor, fn 1468), then the std::shared_ptr at +24 and the one at +16, and stores no vptr first: a final class.
//
// The layout: +11, +12 and +13 three bytes, each the id vota::CThreadVota::AddStoppedTick (fn 807) returns on
// vota::CThreadOperador for 30000, 15000 and 50 ms, the first in the base's tail padding; +16 and +24 two forms, each
// from api::CMTFormBuilder::GetInteractiveForm (fn 301): ProcessInput reads the first, StartState shows it, and the
// second is "Por favor, aguarde."; +32 the context api::CriaContextoAplicacao (fn 3682) builds with the kind 2. The
// member names are chosen; the bytes' type is the type of AddStoppedTick's result.
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

    void PararTicks();
    void ObtemEstadoPosReconhecimentoBiometrico(const bool reconhecido);
    std::pair<bool, comum::TScoreHabilitacao> VerificaDigital(const api::TSharedImageVector& imagem, const long largura,
                                                              const long altura);
    std::pair<bool, comum::TScoreHabilitacao> VerificaDigitalTreinamento();

    static std::unique_ptr<CPedeDigital> s_inst;
    static std::mutex s_mutex;

    uebyte m_tickLeitura;
    uebyte m_tickTimeout;
    uebyte m_tickVerificacao;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formAguarde;
    api::CApplicationContext m_contexto;
};

} // namespace vota
