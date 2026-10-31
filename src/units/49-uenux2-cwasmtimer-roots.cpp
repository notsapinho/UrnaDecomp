// Roots: keep unit 49's simulador::CWasmTimerScheduler in the skeleton link, reached the way the target reaches it.
// Its one member, slot 0 (fn 7871), builds every timer: a std::make_shared<CWasmTimer> into which binaryen inlined
// CWasmTimer's constructor, its only caller here as in the target, which brings std::__shared_ptr_emplace<CWasmTimer>
// and the vtable the constructor stores, through which the target reaches CWasmTimer's other members. The slot is
// reached through the scheduler's vtable only (7871 has no direct caller), and the one reference to that vtable is the
// vptr store of fn 8302, simulador's start, which is not reconstructed. So this file takes the vtable's address, the
// reference that store gives; no constructor is called. Declared through an asm label, so this TU needs no uenux2 header
// and instantiates nothing.
extern const char cwasmtimerscheduler_vt[] __asm__("_ZTVN9simulador19CWasmTimerSchedulerE");

namespace {

const void* volatile w7871_sink;

struct SW7871Roots {
    SW7871Roots()
    {
        w7871_sink = cwasmtimerscheduler_vt;
    }
} w7871_roots;

} // namespace
