// Roots: keep api::teste::CPowerMock's and api::teste::CUrnaMock's vtables in the skeleton link the way the target keeps
// them. Neither class has a key function in the target: every member is inline or pure (api/hwil/ipower.h, iurna.h and
// the two mock headers), and the vtables, their slots, the typeinfos and the destructors are emitted by the TU that
// builds the objects, the TU of fn 8302 (simulador's init), which is not reconstructed. The target reaches every member
// through those vtables only: none has a direct caller (ledger/callgraph.tsv has no line whose callee is one of them).
// A vtable with no key function is emitted only by a TU that uses it: the two optnone functions below build the objects
// as fn 8302 does, so clang emits the implicit constructors here and with them both vtables, every member they name and
// the typeinfos (as COMDATs). They are not rooted, so wasm-ld drops them and the constructors: the target has no function
// of its own for a constructor either, clang inlined both. The static constructor takes the two vtables' addresses, the
// reference the target's vptr stores give, which keeps every slot. This file includes the unit's headers: it stands for
// the TU that emits these members, as unit 67's does, and the unit has no other object to emit them.
#include "mock/api/hwil/cpowermock.h"
#include "mock/api/hwil/curnamock.h"

extern "C" {
extern const char cpowermock_vt[] __asm__("_ZTVN3api5teste10CPowerMockE");
extern const char curnamock_vt[] __asm__("_ZTVN3api5teste9CUrnaMockE");
}

__attribute__((optnone, noinline)) api::IPower* cpowermock_emite()
{
    return new api::teste::CPowerMock;
}

__attribute__((optnone, noinline)) api::IUrna* curnamock_emite()
{
    return new api::teste::CUrnaMock;
}

namespace {

const void* volatile hwil_sink;

struct SHwilRoots {
    SHwilRoots()
    {
        hwil_sink = cpowermock_vt;
        hwil_sink = curnamock_vt;
    }
} hwil_roots;

} // namespace
