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

// vota::CJustificativaEfetuada (RTTI: si_class of comum::CAppState; vtable @1589804 [448, 765, 10594, 7480, 1661, 218,
// 425, 10593, 425]): an operator's screen, whose title StartState sets to one of two literals, cjustificativaefetuada.cpp
// has them. It overrides the destructors, StartState (slot 2, fn 10594) and ProcessInput (slot 7, fn 10593, which goes
// to vota::CCancelaHabilitacaoEleitor on api::INPUT_CONFIRMA). A singleton: fn 2747 (GetInst, the name the project's
// singletons use) creates the 32-byte object on first use and keeps it in a static
// std::unique_ptr (@1905952) under a static std::mutex (@1905928), destroyed at exit by fns 10597 and 10595; the
// constructor, inlined there, passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and stores what the layout below holds. The destructor is out of
// line: the deleting one (fn 765) calls it and frees `this`, and it stores no vptr, as a final class's; 19 states share
// the two bodies, fns 448 and 765. GetInst (fn 2747) holds the constructor inlined, which initializes the form from a
// helper that builds it and takes the title by value (2747 adds a reference to the string's block before building the
// form and drops it after, the shape of vota::CEleitorVotouNaoVotou's 1901), and sets +28. Its callers are
// IIniciaJustificativa::StartState (fn 10587), which calls it twice, clearing +28 through the first call's result, and
// fn 10590.
//
// The layout: +12 a std::shared_ptr<std::string>, which fn 2747 builds with std::make_shared (control block vptr 1588328,
// __shared_ptr_emplace<std::string>) from "justificou/ja justificou" and hands to the form's builder, and which
// StartState overwrites with the screen's title; +20 the form, from api::CMTFormBuilder::GetInteractiveForm (fn 301),
// which ProcessInput reads through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record
// cinteractiveform.h:57 @1589860); +28 a byte fn 2747 sets to 1 and StartState tests against 1, the first branch logging
// "Justificativa recebida"; fn 10587 clears it before it goes to this state. bool is a choice
// (docs/reference/facts/reading.md R14: a store of 0 and of 1 and one read do not tell a bool from a byte), and so are
// the member names and SetRecebida, the setter 10587's store is written through (a public member is the other form, not
// tried).
class CJustificativaEfetuada final : public comum::CAppState {
public:
    virtual ~CJustificativaEfetuada() override;

    static CJustificativaEfetuada& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

    void SetRecebida(bool recebida) { m_bRecebida = recebida; }

private:
    CJustificativaEfetuada();

    static std::unique_ptr<CJustificativaEfetuada> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<std::string> m_titulo;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    bool m_bRecebida;
};

} // namespace vota
