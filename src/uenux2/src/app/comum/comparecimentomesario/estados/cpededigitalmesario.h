#pragma once

#include <memory>
#include <mutex>

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

namespace comum {

class IControladorRegistraMesarios;

// comum::CPedeDigitalMesario (RTTI: si_class of comum::CAppState; vtable @1595328 [1537, 3629, 10318, 7480, 1661,
// 10315, 425, 10317, 10316]): it overrides StartState (slot 2, fn 10318), FinishState (slot 5, fn 10315, a thunk into
// binaryen's fn 6012), ProcessInput (slot 7, fn 10317), which goes back to asking for the titulo on CORRIGE, and
// ProcessTick (slot 8, fn 10316); the records of cpededigitalmesario.cpp name StartState, FinishState and ProcessTick.
// StartState and FinishState are written; ProcessTick is pending (src/units/135-uenux2-comum-mesario-estados-pending.cpp).
// The destructor is out of line: the deleting one (fn 3629) calls it and frees `this`, and it stores no vptr, as a final
// class's; vota::CPedeIdentidade and vota::CRegistraDigitalOperador share both bodies (fns 1537 and 3629).
//
// The layout is what the constructor stores, which comum::IPedeTituloMesario::ProcessInput (fn 10313) holds inlined
// by binaryen with GetInst: CAppState's with EVENTO_ENTRADA | EVENTO_TICK (6); +11 and +12 the bytes the controller's
// slot 2 returns for 15000 and 50 (AddTick), the ticks StartState starts through slot 4; +16 the form ProcessInput reads,
// and +24 a second form of the same type, "Por favor, aguarde.", which the destructor releases first: the constructor
// builds both with api::CMTFormBuilder::GetInteractiveForm (fn 301) in place. The members' names are chosen. A singleton:
// GetInst keeps the object in a static std::unique_ptr (@1909904, destroyed at exit by fn 10321, a thunk into fn 3886)
// under a static std::mutex (@1909880, by fn 10320). GetControlador's record (cpededigitalmesario.cpp:304) names it a
// non-static, non-const member returning `const IControladorRegistraMesarios &`, as in the other mesario states.
// src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which is chosen.
class CPedeDigitalMesario final : public CAppState {
public:
    virtual ~CPedeDigitalMesario() override;

    static CPedeDigitalMesario& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte id) override;

private:
    CPedeDigitalMesario();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeDigitalMesario> s_inst;

    uebyte m_tickCaptura;
    uebyte m_tickEspera;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formAguarde;
};

// The operator's two forms of this state, which the constructor builds in place. Fn 10313 holds them inlined by binaryen,
// behind a 64-byte and a 48-byte frame: the first asks for the mesario's finger and names the mesario through the file's
// anonymous CNomeMesariosUrnaDS::Text (fn 10319, record cpededigitalmesario.cpp:47, a thunk into binaryen's fn 6008,
// shared with cdigitalmesarionaoreconhecida.cpp's class of that name, fn 10323), the second says "Por favor, aguarde.".
// Their names and their being free functions of comum with external linkage are chosen
// (src/units/135-uenux2-comum-mesario-estados.mk).
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaPedeDigitalMesario();
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaAguardeDigitalMesario();

} // namespace comum
