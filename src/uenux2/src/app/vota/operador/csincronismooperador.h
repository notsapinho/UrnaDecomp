#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CSincronismoOperador (RTTI: si_class of comum::CAppState; vtable @1601144 [174, 144, 10210, 7480, 1661, 218,
// 10209, 218, 425]): it overrides StartState (slot 2) and ProcessKey (slot 6). The object stays 12 bytes: a byte at
// +11, in the base's tail padding, which the constructor clears and ProcessKey (fn 10209) reads as a bool; its name
// and type are chosen. final: fn 1897 deletes the old object with no call through the vtable. A singleton: GetInst (fn
// 1897) keeps the object in a static std::unique_ptr (@1911680, destroyed at exit by fn 10213) under a static
// std::mutex (@1911656, by fn 10211). The constructor passes 1 to the base's. src/units/104-uenux2-app-vota-estados.mk
// says which of this is evidence and which is chosen.
class CSincronismoOperador final : public comum::CAppState {
public:
    static CSincronismoOperador& GetInst();

    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;

private:
    CSincronismoOperador();

    static std::mutex s_mutex;
    static std::unique_ptr<CSincronismoOperador> s_inst;

    bool m_bSincronizado;
};

} // namespace vota
