// Roots: keep unit 99's functions in the skeleton link the way the target keeps them. The target reaches CWasmThread's
// members through the vtable (@1528392), which the factory api::CDefaultGenericFactory<IThreadImpl, CWasmThread> of the
// executable TU stores (fn 10878, in the link), so the vtable needs no sink here. That TU reaches the three wrappers of
// wasmjs.cpp through `invoke_vii(59, ...)`,
// `invoke_vi(105, ...)` and `invoke_vi(104, ...)` (fns 7840, 10384, 10619, 10857; 10703; 10857): by their table slots.
// 10703 (votaPressKey), 10619 (votaTick) and 10857 are unit 170's and take the addresses themselves, as 10384 (main's
// lambda) takes EmitEvent's; EmitEvent's is taken here for 7840 (votaInit), not written. ConsoleError's one slot user,
// 10857, is in the link. Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
void emit_event(const char*, const void*) __asm__("_ZN9simulador9EmitEventEPKcRKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
}

namespace {

void (*volatile emit_event_sink)(const char*, const void*);

struct SCWasmThreadRoots {
    SCWasmThreadRoots()
    {
        emit_event_sink = &emit_event;
    }
} cwasmthread_roots;

} // namespace
