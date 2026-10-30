#pragma once

#include "api/hwil/iimpressorarelatorios.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IImpressoraRelatorios, vtable @1530644, 15 slots), the wasm
// build's printer, which prints nothing. The object is 8 bytes (simulador's init, fn 8302, into which the constructor
// is inlined, allocates 8, stores the vptr and 0 at +4), so the class adds no data member to its base's style. Slots 4
// to 7 are inherited; the destructors (slots 10 and 11) are the shared empty bodies 174 and 144, an implicit
// destructor. Every other slot is overridden: their target functions are 340, 425, 218, 8365 and 1870, and only slot
// 12's is not a body binaryen shares with other classes. SetStyle calls slot 12, and fn 3875 calls slot 9, with no
// argument, before a report prints. No caller of the others was found, so the target shows no more of them than their
// wasm types and, for slots 0 and 13, that they return 0. Which of them are defined in the class is chosen, here all in
// the .cpp. The class is not known to be final: no member is called on it directly, and `final` gives the same object.
class CWasmNullPrinter : public api::IImpressoraRelatorios {
public:
    int Slot0() override;
    void Slot1(int valor) override;
    void Slot2() override;
    void Slot3() override;
    void Slot8() override;
    void Slot9() override;
    void ApplyStyle(api::ELPStyle style) override;
    int Slot13() override;
    void Slot14(int a, int b, int c) override;
};

} // namespace simulador
