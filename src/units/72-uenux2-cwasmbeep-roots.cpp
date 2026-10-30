// Roots: keep unit 72's simulador::CWasmBeep in the skeleton link, reached the way the target reaches it.
// The target creates its one CWasmBeep in simulador's init (fn 8302, not reconstructed), into which the constructor is
// inlined: operator new(4), the vptr store and js_wasm_beep_init. Every member is reached through that vtable only
// (`awk -F'\t' '$2==8533' ledger/callgraph.tsv` and the same for the other slots print nothing; each fills one
// table slot, the vtable's). So this file takes the vtable's address, the reference the constructor's vptr store
// gives, which keeps every slot; the constructor itself has no caller here, as it has no function of its own in the
// target. The tone-sequence functions of api/hwil/ibeep.cpp are not rooted: each has one caller, a CWasmBeep member,
// into which binaryen inlines it as in the target. Declared through an __asm__ label, no header; compiled with
// APP_CXXFLAGS.
extern const char w8533_vt[] __asm__("_ZTVN9simulador9CWasmBeepE");

namespace {

const void* volatile w8533_sink;

struct SW8533Roots {
    SW8533Roots()
    {
        w8533_sink = w8533_vt;
    }
} w8533_roots;

} // namespace
