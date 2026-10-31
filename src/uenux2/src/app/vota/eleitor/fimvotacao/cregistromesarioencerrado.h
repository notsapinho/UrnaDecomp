#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CRegistroMesarioEncerrado (RTTI: si_class of comum::CAppState; vtable @1586768 [174, 144, 10763, 7480, 1661, 218,
// 10762, 218, 425]): it overrides StartState (slot 2) and ProcessKey (slot 6) and adds no data member, so the object is
// the base's 12 bytes (fn 10793 allocates 12), and slots 0 and 1 hold the destructors the states with no member share
// (fns 174 and 144). final: fn 10793 frees the old object with no call through the vtable. A singleton: GetInst, which
// binaryen inlined into its one caller, vota::CControladorRegistraMesariosVota's slot 11 (fn 10793), keeps the object
// in a static std::unique_ptr (@1904888, destroyed at exit by fn 10765) under a static std::mutex (@1904864, by fn
// 10764). The constructor passes 1 to the base's. No record names the class or its file; unit 119's fragment says
// which of this is evidence and which is chosen.
class CRegistroMesarioEncerrado final : public comum::CAppState {
public:
    static CRegistroMesarioEncerrado& GetInst();

    virtual void StartState() override;
    virtual void ProcessKey(uebyte tecla) override;

private:
    CRegistroMesarioEncerrado();

    static std::mutex s_mutex;
    static std::unique_ptr<CRegistroMesarioEncerrado> s_inst;
};

} // namespace vota
