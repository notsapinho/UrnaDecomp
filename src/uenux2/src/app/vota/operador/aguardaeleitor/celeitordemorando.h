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

// vota::CEleitorDemorando (RTTI: si_class of comum::CAppState; vtable @1592784 [1284, 2884, 10440, 7480, 1661, 218,
// 5394, 10439, 425]): the operator is told that the voter is taking long. It overrides the destructors, StartState
// (slot 2, fn 10440), ProcessKey (slot 6, fn 5394, one body with vota::CPerguntaEleitorVotando's slot 6) and
// ProcessInput (slot 7, fn 10439). The destructor is out of line: slots 0 and 1 are fns 1284 and 2884, the bodies
// binaryen keeps once for the states with three std::shared_ptr at +12, +20 and +28. A singleton: GetInst (fn 2734)
// creates the 36-byte object on first use under a static std::mutex (@1909208, destroyed at exit by fn 10441) and keeps
// it in a static std::unique_ptr (@1909232, by fn 10442); the constructor, inlined there behind a frame of its own,
// passes comum::CAppState::EVENTO_TECLA | comum::CAppState::EVENTO_ENTRADA (3) to the base's and fills the layout
// below. Its one target caller is vota::CMostraEleitorVotando::ProcessKey (fn 10425), four times.
//
// The layout: +11 a byte the constructor clears and StartState tests to choose the text of +12 ("Votou parcialmente" or
// "Não votou") and copies into vota::CSuspensaoAutomaticaEleitor's +11; +12 and +20 two std::shared_ptr<std::string>,
// each std::make_shared'd (control block vptr 1588328), from "votou/não votou" and "nome abreviado", each the text of a
// field of the form, +20 set by StartState from vota::CThreadOperador's text of the voter (its string at +108); +28 the
// form, which ProcessInput reads through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record
// cinteractiveform.h:57 @1592840). bool for the byte and every member name are chosen; nothing here writes the byte but
// the constructor and vota::CMostraEleitorVotando::ProcessKey (fn 10425: false on its key 3, true on its key 4,
// before it goes here), through SetVotou, a setter whose name is chosen, as CEleitorVotouNaoVotou's.
class CEleitorDemorando final : public comum::CAppState {
public:
    virtual ~CEleitorDemorando() override;

    static CEleitorDemorando& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

    void SetVotou(bool votou) { m_bVotou = votou; }

private:
    CEleitorDemorando();

    static std::unique_ptr<CEleitorDemorando> s_inst;
    static std::mutex s_mutex;

    bool m_bVotou;
    std::shared_ptr<std::string> m_situacao;
    std::shared_ptr<std::string> m_texto;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
