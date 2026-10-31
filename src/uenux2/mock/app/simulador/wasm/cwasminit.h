#pragma once

#include <vector>

#include "app/comum/iinterfaceinit.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of comum::IInterfaceInit, vtable @1528764), the wasm build's platform
// start. Its object is 28 bytes: fn 8302 allocates 28, runs IInterfaceInit's constructor inline (its members at +4 and
// +12), stores a 32-bit value at +24 and then this class's vptr; slot 4 (fn 9418) returns that value. The other slots
// answer as a platform with nothing behind it: slot 2 returns 1 and slot 3 true (one shared body, fn 434), slot 6 false
// (fn 340), slot 7 does nothing (fn 425), and slot 5 (fn 9405) logs each message it gets through fn 1524, which formats
// "CWasmInit::{} {}", and answers with a value per message. The destructor is implicit: slot 0 is IInterfaceInit's (fn
// 5898) and slot 1 (fn 9388) frees what that returns (docs/reference/facts/reading.md R5, the shape around an
// out-of-line base D2). Slot4 and EnviarMensagem are out of line: in their use band 9418 and 9405 run before 9388, the
// deleting destructor clang emits after a file's external functions, and the vtable and typeinfo (1528764, 1528804) lie
// between CWasmNullTextToSpeech's and CWasmScreen's, so this class's own TU emits them. Slots 2, 3, 6 and 7 are shared
// bodies, so where they are defined is chosen: in the class. The member names are IInterfaceInit's (chosen there); the
// data member's name and type, the constructor's parameter and that the constructor is inline are chosen (binaryen or
// clang inlined it into fn 8302, which only that shows).
class CWasmInit : public comum::IInterfaceInit {
public:
    explicit CWasmInit(int parametro) : m_parametro(parametro) {}

    comum::EBootDeviceId CurrentBootDevice() override { return comum::BOOT_DEVICE_1; }
    bool Slot3() override { return true; }
    int Slot4() override;
    std::vector<int> EnviarMensagem(ueint32 mensagem) override;
    bool Slot6() override { return false; }
    void Slot7(int) override {}

private:
    int m_parametro;
};

} // namespace simulador
