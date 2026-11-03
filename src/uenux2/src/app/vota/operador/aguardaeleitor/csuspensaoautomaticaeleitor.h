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

// vota::CSuspensaoAutomaticaEleitor (RTTI: si_class of comum::CAppState; vtable @1593264 [2732, 10411, 10409, 7480,
// 1661, 10408, 10404, 10407, 10405]): the operator's screen that suspends the voter on a timer. It overrides the
// destructors (slots 0 and 1, fns 2732 and 10411), StartState (slot 2, fn 10409), FinishState (slot 5, fn 10408),
// ProcessKey (slot 6, fn 10404), ProcessInput (slot 7, fn 10407) and ProcessTick (slot 8, fn 10405). The destructor is
// out of line: the deleting one (fn 10411) calls it and frees `this`; it stores no vptr, as a final class's
// (docs/reference/facts/reading.md R4, R5). A singleton: GetInst has no target function of its own, fn 10440
// (vota::CEleitorDemorando::StartState) holds it inlined (the one store of the vptr, 1593272), with the 56-byte object
// kept in a static std::unique_ptr (@1909400, destroyed at exit by fn 10414) under a static std::mutex (@1909376, fn
// 10412); the constructor, inlined there behind a 96-byte frame of its own, passes comum::CAppState::EVENTO_TECLA |
// EVENTO_ENTRADA | EVENTO_TICK (7) to the base's and fills the layout below, the form from a helper clang inlines.
// 10440 then copies vota::CEleitorDemorando's byte at +11 into this class's +11 (SetVotou, a setter whose name is
// chosen). The record at csuspensaoautomaticaeleitor.cpp:89 names DisparaSinalizacaoSonora's lambda (fn 10410).
//
// The layout: +11 a byte StartState tests to choose the text it writes into +28's string; +12 the id of the tick that
// FinishState, ProcessKey and ProcessInput stop (CThreadVota::StopTick takes a uebyte) and StartState sets from
// CThreadVota::AddStoppedTick; +16 a signed 64-bit count StartState sets to 10 and ProcessTick counts down
// (`i64.ge_s`); +24 a byte FinishState and ProcessKey clear and ProcessTick sets; +28 and +36 two std::shared_ptr to
// strings the constructor makes with std::make_shared (fn 10440 stores the vptr of
// __shared_ptr_emplace<std::string> into both blocks; StartState assigns a C string to +28's); +44 the form, read
// through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (fn 10407). The D2 (fn 2732) releases +44, +36
// and +28 in that order. The member names, bool for the two bytes and ueint64 are chosen.
class CSuspensaoAutomaticaEleitor final : public comum::CAppState {
public:
    virtual ~CSuspensaoAutomaticaEleitor() override;

    static CSuspensaoAutomaticaEleitor& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte tick) override;

    void SetVotou(bool votou) { m_bVotou = votou; }

private:
    CSuspensaoAutomaticaEleitor();

    static std::unique_ptr<CSuspensaoAutomaticaEleitor> s_inst;
    static std::mutex s_mutex;

    void InicializaTick();

    void AtualizaMensagem();

    void DisparaSinalizacaoSonora();

    bool m_bVotou;
    uebyte m_tick;
    ueint64 m_contagem;
    bool m_bSinalizado;
    std::shared_ptr<std::string> m_situacao;
    std::shared_ptr<std::string> m_mensagem;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
