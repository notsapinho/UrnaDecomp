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

// vota::CConfirmaAudio (RTTI: si_class of comum::CAppState; vtable @1587140 [244, 387, 1070, 7480, 1661, 218, 425,
// 10740, 425]): the operator confirms turning the audio on or off. It overrides the destructors, StartState (slot 2,
// fn 1070, the body it shares with comum::CDigitalMesarioNaoReconhecida's and other states' StartState: the next state
// is the state itself, then the form's slot 2) and ProcessInput (slot 7, fn 10740: vota::CHabilitaAudioManualmente on
// api::INPUT_CONFIRMA, vota::CEscolheOpcao on api::INPUT_CORRIGE). Slots 0 and 1 are fns 244 and 387, the out-of-line
// destructors 49 final states share: a std::shared_ptr at +12, the form, is all they release; ProcessInput reads it
// through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1587196). A
// singleton: GetInst creates the 20-byte object under a static std::mutex (@1904976) and keeps it in a static
// std::unique_ptr (@1905000). Its one caller, vota::CEscolheOpcao's ConfirmaOpcao (inlined into fn 10689), holds it
// inlined with the constructor behind a 64-byte frame of its own, so it has no target function: written in
// cconfirmaaudio.cpp, it has that one call site in our link too. The form's second field is the text of fn 10742,
// passed by table slot (TextoConfirmaAudio, defined there). The member names are chosen.
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CConfirmaAudio final : public comum::CAppState {
public:
    virtual ~CConfirmaAudio() override;

    static CConfirmaAudio& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CConfirmaAudio();

    static std::unique_ptr<CConfirmaAudio> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
