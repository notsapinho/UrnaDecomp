#pragma once

#include "api/hwil/iinput.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IInputMT, vtable @1530136): the vtable of CWasmInputKbd without
// its last three slots, over the same key queue. Its object is 8 bytes, as CWasmInputKbd's: fn 8302 stores the vptr
// and 0 at +4. The member names are IInput's, chosen.
class CWasmInputMT : public api::IInputMT {
public:
    virtual char ReadKey() override;
    virtual bool HasKey() override;
    virtual void Clear() override;
};

} // namespace simulador
