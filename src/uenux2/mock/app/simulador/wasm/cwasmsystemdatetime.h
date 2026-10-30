#pragma once

#include "api/util/isystemdatetime.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::ISystemDateTime, vtable @1532044). Its object is 16 bytes: fn
// 8302 allocates 16, stores 0 at +8 as an i64 and stores the vptr. Slot 0 adds that i64 to the browser's clock, and slot
// 1 stores the given time less the browser's clock: an offset between the two, zero until the clock is set. The
// destructors are the shared empty ones (slots 2 and 3: 174, 144), left implicit. The member names are
// ISystemDateTime's, chosen, and so is the data member's.
class CWasmSystemDateTime : public api::ISystemDateTime {
public:
    virtual time_t GetTime() override;
    virtual void SetTime(time_t agora) override;

private:
    time_t m_diferenca = 0;
};

} // namespace simulador
