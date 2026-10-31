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

// comum::CPedeDigitalMesario (RTTI: si_class of comum::CAppState; vtable @1595328 [1537, 3629, 10318, 7480, 1661,
// 10315, 425, 10317, 10316]): it overrides StartState (slot 2, fn 10318), FinishState (slot 5, fn 10315, a thunk into
// binaryen's fn 6012), ProcessInput (slot 7, fn 10317), which goes back to asking for the titulo on CORRIGE, and
// ProcessTick (slot 8, fn 10316); the records of cpededigitalmesario.cpp name StartState, FinishState and ProcessTick,
// and those three are pending (src/units/135-uenux2-comum-mesario-estados-pending.cpp). The destructor is out of line:
// the deleting one (fn 3629) calls it and frees `this`, and it stores no vptr, as a final class's;
// vota::CPedeIdentidade and vota::CRegistraDigitalOperador share both bodies (fns 1537 and 3629). The layout is what
// the slots and the destructor read: +11 and +12 the two ticks StartState starts through the controller's slot 4, +16
// the form ProcessInput reads, and +24 a second std::shared_ptr, which the destructor releases first, whose pointee no
// body here shows (chosen: the voter's form, as in the other mesario states). A singleton: GetInst keeps the object in
// a static std::unique_ptr (@1909904, destroyed at exit by fn 10321, a thunk into fn 3886) under a static std::mutex
// (@1909880, by fn 10320). GetInst, its constructor and the file's anonymous CNomeMesariosUrnaDS (fn 10319, record
// cpededigitalmesario.cpp:47) are not reconstructed. src/units/135-uenux2-comum-mesario-estados.mk says which of this
// is evidence and which is chosen.
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

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeDigitalMesario> s_inst;

    uebyte m_tickCaptura;
    uebyte m_tickEspera;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

} // namespace comum
