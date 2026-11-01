#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CGeraDadosDinamicos (RTTI: si_class of comum::CAppState; vtable @1545964 [174, 144, 11865, 7480, 1661, 218, 425,
// 218, 425]): it overrides StartState (slot 2, fn 11865, record cgeradadosdinamicos.cpp:47, pending) and adds no data
// member, so the object is the base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share
// (fns 174 and 144). final: GetInst deletes the old object with no call through the vtable. A singleton: GetInst,
// inlined by binaryen into its one caller, vota::testeteclado::CPreZeresima::GetEstadoPassouNoTeste (fn 5945), keeps
// the object in a static std::unique_ptr (@1834716, destroyed at exit by fn 11867) under a static std::mutex
// (@1834692, by fn 11866); the constructor passes 0 to the base's. src/units/104-uenux2-app-vota-estados.mk has the
// evidence for that shape. GetInst, the statics' names, StartState as the key function and this header's path, beside
// the .cpp its record names, are chosen.
class CGeraDadosDinamicos final : public comum::CAppState {
public:
    static CGeraDadosDinamicos& GetInst();

    virtual void StartState() override;

private:
    CGeraDadosDinamicos();

    static std::mutex s_mutex;
    static std::unique_ptr<CGeraDadosDinamicos> s_inst;
};

} // namespace vota
