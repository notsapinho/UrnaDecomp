#pragma once

#include <memory>
#include <string>
#include <utility>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPerguntaCodigoSuspensao (RTTI: si_class of comum::CAppState; vtable @1593120 [448, 765, 10421, 7480, 1661, 218,
// 10419, 10420, 425]): an operator's screen; StartState logs that the voter's title was asked for to suspend the voter.
// It overrides the destructors, StartState (slot 2, fn 10421), ProcessKey (slot 6, fn 10419, pending) and ProcessInput
// (slot 7, fn 10420). A singleton: fn 10415 creates the 32-byte object on first use and keeps it in a static
// std::unique_ptr (@1909344) under a static std::mutex (@1909320), destroyed at exit by fns 10423 and 10422 (elem 4228
// and 4229, right before this vtable's slots). The constructor, inlined there, passes comum::CAppState::EVENTO_TECLA |
// comum::CAppState::EVENTO_ENTRADA (3) to the base's and stores what the layout below holds. The destructor is out of
// line: the deleting one (fn 765) calls it and frees `this`, and it stores no vptr, as a final class's; 19 states share
// the two bodies, fns 448 and 765. Not recovered: the constructor and GetInst (fn 10415, which holds them inlined, calls
// fns 1150 and 1151, which have no name, 501, api::CPriorityMessageQueue<api::SMessage>::Insert, and 1398,
// comum::IEventosLog::logaAlerta).
//
// The layout: +12 and +20 two forms, each from api::CMTFormBuilder::GetInteractiveForm (fn 301); StartState shows the
// first, and ProcessInput shows the second when the title typed is not valid, then the first again. +28 a byte that the
// constructor and StartState set to 0, ProcessKey (fn 10419) too on keys 2 and 13, and ProcessInput to 1 once a valid
// title was typed; ProcessInput reads the form and stops there while it is set. bool is the plainest type of that
// width, a choice, and so are the member names.
class CPerguntaCodigoSuspensao final : public comum::CAppState {
public:
    virtual ~CPerguntaCodigoSuspensao() override;

    static CPerguntaCodigoSuspensao& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

private:
    CPerguntaCodigoSuspensao();

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formConfirmacao;
    bool m_bLido;
};

// ProcessInput's check of the title typed (fn 10420 holds it inlined by binaryen, in a 48-byte frame of its own):
// whether it is a valid voter's title (comum::md::CValidadorIdentidade) other than the identity typed for the voter,
// and the title formatted. It reads no state of the class. Its name, its result's type and its being a free function
// declared here are chosen; validatitulosuspensao.cpp defines it.
std::pair<bool, std::string> ValidaTituloSuspensao(const std::string& titulo);

} // namespace vota
