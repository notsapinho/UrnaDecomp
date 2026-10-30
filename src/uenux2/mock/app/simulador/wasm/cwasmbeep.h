#pragma once

#include "api/hwil/ibeep.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IBeep, vtable @1530304). The object is 4 bytes, the vptr only:
// simulador's init (fn 8302, into which the constructor is inlined) allocates 4 bytes, stores the vptr and calls
// js_wasm_beep_init. The destructors are the shared empty ones (slots 7 and 8: fns 174 and 144): an implicit destructor
// or one defined in the class, and it is left implicit here. The class is not final: its members call slot 1 through
// the vtable, which `final` would make a direct call. The member names are api::IBeep's, chosen (api/hwil/ibeep.h says
// from what).
class CWasmBeep : public api::IBeep {
public:
    CWasmBeep();

    virtual void SetVolume(int volume) override;
    virtual void Beep(int frequency, int duration) override;
    virtual void BeepConfirm(int times) override;
    virtual void BeepError() override;
    virtual void BeepAlert() override;
    virtual void BeepDiscard() override;
    virtual void BeepKey() override;
};

} // namespace simulador
