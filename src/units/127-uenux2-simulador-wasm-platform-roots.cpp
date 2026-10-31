// Roots: keep unit 127's classes in the skeleton link, reached the way the target reaches them. Every member of
// simulador::CWasmInit and CWasmResource is reached through its vtable only (no member has a
// direct caller: each `fn` readout says `uses 0`), and the one reference to each vtable is the vptr store of fn 8302,
// simulador's start, which builds both objects and is not reconstructed. So this file takes each vtable's address,
// the reference those stores give, which keeps every slot; no constructor is called. Declared through asm labels, so
// this TU needs no uenux2 header and instantiates nothing.
extern const char cwasminit_vt[] __asm__("_ZTVN9simulador9CWasmInitE");
extern const char cwasmresource_vt[] __asm__("_ZTVN9simulador13CWasmResourceE");

namespace {

const void* volatile platform_sink;

struct SPlatformRoots {
    SPlatformRoots()
    {
        platform_sink = cwasminit_vt;
        platform_sink = cwasmresource_vt;
    }
} platform_roots;

} // namespace
