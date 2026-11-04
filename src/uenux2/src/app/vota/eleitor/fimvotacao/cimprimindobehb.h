#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CImprimindoBEHB (RTTI: si_class of comum::CAppState; vtable @1541428 [174, 144, 12074, 7480, 1661, 218, 425,
// 218, 425]): it overrides StartState (slot 2, fn 12074, records cimprimindobehb.cpp 45 and 46) and adds no data
// member, so the object is the base's 12 bytes, and slots 0 and 1 hold the destructors the states with no member share
// (fns 174 and 144). StartState asserts the vote's and the closing's states, prints the report of the voters enabled by
// their biographical data (ImprimeRelatorio, record cimprimindobehb.cpp:55, `void vota::CImprimindoBEHB::ImprimeRelatorio()`,
// out of line in the object: fn 12074 holds it behind a second stack-pointer prologue) and goes to vota::CRetirarMR. A
// singleton: GetInst, inlined into vota::CImprimindoBim::StartState (fn 12071), keeps the object in a static
// std::unique_ptr (@1833680, destroyed at exit by fn 12076) under a static std::mutex (@1833656, by fn 12075), and builds
// it as the base's constructor with 0 and the vptr 1541436, CImprimindoBim's shape (src/units/104-uenux2-app-vota-estados.mk).
// Chosen: the names GetInst, s_inst and s_mutex, ImprimeRelatorio's being private, and this header's path, beside the
// .cpp the records name.
class CImprimindoBEHB final : public comum::CAppState {
public:
    static CImprimindoBEHB& GetInst();

    virtual void StartState() override;

private:
    CImprimindoBEHB();

    void ImprimeRelatorio();

    static std::mutex s_mutex;
    static std::unique_ptr<CImprimindoBEHB> s_inst;
};

} // namespace vota
