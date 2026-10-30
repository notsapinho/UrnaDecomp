// Roots: keep unit 99's functions in the skeleton link the way the target keeps them. The target reaches CWasmThread's
// members through the vtable (@1528392), which the factory api::CDefaultGenericFactory<IThreadImpl, CWasmThread> of the
// executable TU stores (not reconstructed). That TU reaches the three wrappers of wasmjs.cpp through `invoke_vii(59, ...)`,
// `invoke_vi(105, ...)` and `invoke_vi(104, ...)` (fns 7840, 10384, 10619, 10857; 10703; 10857): by their table slots, so
// each has its own address taken here. Declared through asm labels, so this TU needs no uenux2 header and instantiates
// nothing.
extern "C" {
extern const char cwasmthread_vt[] __asm__("_ZTVN9simulador11CWasmThreadE");
void emit_event(const char*, const void*) __asm__("_ZN9simulador9EmitEventEPKcRKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void push_key(const void*) __asm__("_ZN9simulador7PushKeyERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
void console_error(const void*) __asm__("_ZN9simulador12ConsoleErrorERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
}

namespace {

const void* volatile cwasmthread_sink;
void (*volatile emit_event_sink)(const char*, const void*);
void (*volatile push_key_sink)(const void*);
void (*volatile console_error_sink)(const void*);

struct SCWasmThreadRoots {
    SCWasmThreadRoots()
    {
        cwasmthread_sink = cwasmthread_vt;
        emit_event_sink = &emit_event;
        push_key_sink = &push_key;
        console_error_sink = &console_error;
    }
} cwasmthread_roots;

} // namespace
