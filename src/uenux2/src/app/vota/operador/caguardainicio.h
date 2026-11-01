#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CAguardaInicio (RTTI: si_class of comum::CAppState; vtable @1601032 [244, 387, 10220, 7480, 1661, 10219, 10217,
// 218, 10218]): the operador's screen before the voting starts. It overrides the destructors, StartState (slot 2, fn
// 10220), FinishState (slot 5, fn 10219), ProcessKey (slot 6, fn 10217, pending) and ProcessTick (slot 8, fn 10218). A
// singleton: GetInst (fn 5343, not reconstructed) creates the 24-byte object on first use, with the constructor
// inlined, and keeps it in a static std::unique_ptr (@1911624), releasing @1911600 at the end (fn 150) as the landed
// states' GetInst release their static std::mutex; it deletes an old
// object with a direct call of fn 244 (the D2), so the class is final, and its destructor is out of line: fn 387 calls
// fn 244 and frees `this`, the bodies 49 states share. The constructor passes comum::CAppState::EVENTO_TECLA |
// EVENTO_TICK (5) to the base's.
//
// The layout: +12 the form, from api::CMTFormBuilder::GetForm (fn 1694, in fn 5343); +20 the id of a stopped tick of
// vota::CThreadOperador, 500 ms (fn 807, CThreadVota::AddStoppedTick, in fn 5343), which StartState starts, FinishState
// stops and ProcessTick compares. The member names are chosen. No record names this class: the directory and file are
// chosen, app/vota/operador/caguardainicio.cpp, from the data: the vtable lies after cthreadmonitor.cpp's records and
// before vota::CFinalizaOperador's, vota::CSincronismoOperador's and cthreadoperador.cpp's, a run of app/vota/operador/'s
// files in name order where this file's name sorts first.
class CAguardaInicio final : public comum::CAppState {
public:
    virtual ~CAguardaInicio() override;

    static CAguardaInicio& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessKey(uebyte tecla) override;

    virtual void ProcessTick(uebyte id) override;

private:
    CAguardaInicio();

    static std::mutex s_mutex;
    static std::unique_ptr<CAguardaInicio> s_inst;

    std::shared_ptr<api::IForm<api::IScreenMT>> m_form;
    uebyte m_tick;
};

} // namespace vota
