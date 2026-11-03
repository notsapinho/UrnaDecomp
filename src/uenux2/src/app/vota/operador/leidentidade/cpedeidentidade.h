#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IScreenMT;
class IInputMT;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPedeIdentidade (RTTI: si_class of comum::CAppState; vtable @1588232 [1537, 3629, 10680, 7480, 1661, 10678,
// 425, 10677, 10676]): the operator's screen that asks for the voter's identifier. It overrides StartState (slot 2,
// fn 10680, records cpedeidentidade.cpp:62 and :63), FinishState (slot 5, fn 10678), which stops the three ticks,
// ProcessInput (slot 7, fn 10677) and ProcessTick (slot 8, fn 10676, written and not matched), both in
// src/units/161-uenux2-app-vota-operador-identidade.mk. ProcessTick handles the three ticks: on +11's, when the voting
// is blocked by the time, it stops that tick and logs it; on +12's, once vota::impl::IInformacaoThreadOperador's
// inspection time (slot 18) has come, it schedules the next one, posts 12 to vota::CThreadEleitor's queue and goes to
// vota::CAguardaInspecao; on +13's, it sets +16's text by whether the field with the form's focus is empty. The
// destructor is out of line, the body comum::CPedeDigitalMesario and vota::CRegistraDigitalOperador share (fns 1537
// and 3629), which releases the std::shared_ptr at +24 and then the one at +16. The layout is what the slots and the
// destructor read:
// +11, +12 and +13 the three ticks StartState starts through vota::CThreadOperador (fn 700) and FinishState stops
// (fn 422), +16 a std::shared_ptr to a std::string, and +24 the form StartState shows and ProcessInput reads. The
// pointee at +16 is a string: ProcessTick (fn 10676) assigns it "CORRIGE: outras opções" or " " on the third
// tick (fn 276, string::__assign_external, and a one-character store in place). A singleton: GetInst (fn 652) creates
// the 32-byte object under a static std::mutex (@1905312, destroyed at exit by fn 10681) and keeps it in a static
// std::unique_ptr (@1905336, by fn 10682); the constructor, inlined there, passes EVENTO_ENTRADA | EVENTO_TICK (6) to
// the base's, adds the three ticks (60000, 5000 and 1000), makes +16 a std::string " ", builds the form at +24 from a
// copy of it (vota::MontaTelaPedeIdentidade, app/vota/operador/comum/telasoperador.h) and then calls
// vota::AgendaInspecao (fn 3620). The member names are chosen.
// src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is chosen.
class CPedeIdentidade final : public comum::CAppState {
public:
    virtual ~CPedeIdentidade() override;

    static CPedeIdentidade& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte id) override;

private:
    CPedeIdentidade();

    // Held inlined by binaryen in ProcessInput (fn 10677), behind a 32-byte frame of its own that reads the form at
    // +24: the identifier typed, filled to 12 characters with '0', and the next state, or none when nothing was typed.
    // Its name, its result type and its being a member are chosen
    // (src/units/161-uenux2-app-vota-operador-identidade.mk).
    comum::CAppState* ProximoEstadoIdentidadeDigitada();

    static std::unique_ptr<CPedeIdentidade> s_inst;
    static std::mutex s_mutex;

    uebyte m_tickIdentidade;
    uebyte m_tickEspera;
    uebyte m_tickAviso;
    std::shared_ptr<std::string> m_aviso;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// Held inlined by binaryen in CPedeIdentidade::ProcessInput (fn 10677), behind a 16-byte frame of its own: in the
// training mode the first voter's identifier and its type become the typed identity, and the next state is
// vota::CNomeEleitor. It reads nothing of the class; its name, its result type and its being a free function of vota
// with external linkage are chosen (src/units/161-uenux2-app-vota-operador-identidade.mk).
comum::CAppState* ProximoEstadoTreinamento();

} // namespace vota
