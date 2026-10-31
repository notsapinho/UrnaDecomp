#pragma once

#include <memory>
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
// has them. It overrides the destructors, StartState (slot 2, fn 10594) and ProcessInput (slot 7, fn 10593, pending). A singleton: fn
// 2747 (GetInst, the name the project's singletons use) creates the 32-byte object on first use and keeps it in a static
// std::unique_ptr (@1905952) under a static std::mutex (@1905928), destroyed at exit by fns 10597 and 10595; the
// constructor, inlined there, passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and stores what the layout below holds. The destructor is out of
// line: the deleting one (fn 765) calls it and frees `this`, and it stores no vptr, as a final class's; 19 states share
// the two bodies, fns 448 and 765. Not recovered: the constructor and GetInst (fn 2747 calls fn 395, which has no name).
//
// The layout: +12 a std::shared_ptr<std::string>, which fn 2747 builds with std::make_shared (control block vptr 1588328,
// __shared_ptr_emplace<std::string>) from "justificou/ja justificou" and hands to the form's builder, and which
// StartState overwrites with the screen's title; +20 the form, from api::CMTFormBuilder::GetInteractiveForm (fn 301),
// which ProcessInput reads through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record
// cinteractiveform.h:57 @1589860); +28 a byte fn 2747 sets to 1 and StartState tests against 1, the first branch logging
// "Justificativa recebida". bool is a choice (docs/reference/facts/reading.md R14: one read does not tell a bool from a
// byte), and so are the member names.
class CJustificativaEfetuada final : public comum::CAppState {
public:
    virtual ~CJustificativaEfetuada() override;

    static CJustificativaEfetuada& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CJustificativaEfetuada();

    std::shared_ptr<std::string> m_titulo;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    bool m_bRecebida;
};

} // namespace vota
