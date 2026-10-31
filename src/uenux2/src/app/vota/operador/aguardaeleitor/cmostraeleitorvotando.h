#pragma once

#include <memory>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CMostraEleitorVotando (RTTI: si_class of comum::CAppState; vtable @1593000 [448, 765, 10427, 7480, 1661, 218,
// 10425, 10426, 425]). It overrides the destructors, StartState (slot 2, fn 10427, pending), ProcessKey (slot 6, fn
// 10425, pending; records cmostraeleitorvotando.cpp:127 and 159) and ProcessInput (slot 7, fn 10426, record
// cmostraeleitorvotando.cpp:64). A singleton: fn 1150 creates the 28-byte object on first use and keeps it in a static
// std::unique_ptr (@1909316) under a static std::mutex (@1909292), destroyed at exit by fns 10429 and 10428; the
// constructor, inlined there, passes comum::CAppState::EVENTO_TECLA | comum::CAppState::EVENTO_ENTRADA (3) to the base's
// and stores what the layout below holds. The destructor is out of line: the deleting one (fn 765) calls it and frees
// `this`, and it stores no vptr, as a final class's; 19 states share the two bodies, fns 448 and 765. Not recovered: the
// constructor and GetInst (fn 1150, whose callees all have names, but which passes the form's builder the table slots
// of fns 11529, 10586, 11528, 11527 and 10539, which have no body here).
//
// The layout: +12 a std::shared_ptr<std::string>, which fn 1150 builds empty with std::make_shared (control block vptr
// 1588328, __shared_ptr_emplace<std::string>) and StartState fills from vota::CThreadOperador's string at +108; +20 the
// form, from api::CMTFormBuilder::GetForm (fn 1694). The member names are chosen.
class CMostraEleitorVotando final : public comum::CAppState {
public:
    virtual ~CMostraEleitorVotando() override;

    static CMostraEleitorVotando& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

private:
    CMostraEleitorVotando();

    std::shared_ptr<std::string> m_nome;
    std::shared_ptr<api::IForm<api::IScreenMT>> m_form;
};

} // namespace vota
