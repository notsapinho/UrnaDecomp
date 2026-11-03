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

// vota::CHabilitaAudioManualmente (RTTI: si_class of comum::CAppState; vtable @1586952 [448, 765, 10751, 7480, 1661,
// 218, 425, 218, 425]): the operator turned the audio on or off. It overrides the destructors and StartState (slot 2,
// fn 10751), which toggles vota::SetAudioAtivadoMesario, sets the screen's text and logs it, shows the form, sleeps
// 1000 ms through api::CSystem::Dorme and goes to vota::CPedeIdentidade. The destructor is out of line: slots 0 and 1
// are fns 448 and 765, the bodies 19 states share, which release the std::shared_ptr at +20 and then the one at +12. A
// singleton: GetInst creates the 28-byte object under a static std::mutex (@1904948) and keeps it in a static
// std::unique_ptr (@1904972); binaryen inlines it into its one caller, vota::CConfirmaAudio::ProcessInput (fn 10740),
// with the constructor, which passes EVENTO_ENTRADA (2) to the base's, clears the form's two words, makes +20 a
// std::shared_ptr<std::string> over a new std::string (a __shared_ptr_pointer block, vptr 1587032) and builds the form
// in its body over an api::CTextSource of it.
//
// The layout: +12 the form, which StartState shows (slot 2 of api::IForm); +20 the screen's text, which StartState
// assigns "ÁUDIO ATIVADO" or "ÁUDIO DESATIVADO" (fn 276, string::__assign_external). The member names are chosen.
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CHabilitaAudioManualmente final : public comum::CAppState {
public:
    virtual ~CHabilitaAudioManualmente() override;

    static CHabilitaAudioManualmente& GetInst();

    virtual void StartState() override;

private:
    CHabilitaAudioManualmente();

    static std::unique_ptr<CHabilitaAudioManualmente> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<std::string> m_texto;
};

} // namespace vota
