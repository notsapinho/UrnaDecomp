#pragma once

#include "api/hwil/iinput.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IInputKbd, vtable @1530084). Its object is 8 bytes, the vptr and
// IInput's counter: simulador's init (fn 8302) allocates 8 bytes and stores the vptr and 0 at +4. Slots 0 and 1 are the
// shared empty destructors (174, 144), left implicit. Slots 2 to 4 are one function each with CWasmInputMT's (fns 5015,
// 5014, 5013): two classes with no base between them and their interfaces (RTTI), so two identical bodies binaryen
// merged. Slots 5 to 7 hold the shared empty body 218, and api/hwil/iinput.h says what is chosen about them. Nothing
// shows whether the class is final: no body calls a virtual member. The member names are IInput's and IInputKbd's,
// chosen.
class CWasmInputKbd : public api::IInputKbd {
public:
    virtual char ReadKey() override;
    virtual bool HasKey() override;
    virtual void Clear() override;
    virtual void Slot5() override;
    virtual void Slot6() override;
    virtual void Slot7() override;
};

} // namespace simulador
