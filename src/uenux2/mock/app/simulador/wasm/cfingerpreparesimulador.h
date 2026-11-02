#pragma once

// Reconstruction's note, not TSE's text: simulador::CFingerPrepareSimulador, an si_class of api::IFingerPrepare (RTTI,
// vtable @1526788 among the executable TU's data, so it has no key function). main builds it with a 4-byte operator new
// and its vptr alone, and its slot 2 is fn 218, the empty body many classes share. The header's path and the slot's name
// are chosen.
#include "api/hwil/ifingerprepare.h"

namespace simulador {

class CFingerPrepareSimulador : public api::IFingerPrepare {
public:
    void Prepara() override {}
};

} // namespace simulador
