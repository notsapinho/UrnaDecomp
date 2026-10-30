// Roots: keep simulador::CWasmLogd's vtable in the skeleton link the way the target keeps it. Nothing calls the
// destructors (target fns 8318 and 8316) directly (ledger/callgraph.tsv has no edge into either): the target reaches
// them only through the vtable (@1530800, slots 0 and 1, table entries 742 and 743), whose address the constructor
// inlined into fn 8302 stores. Rooting the vtable keeps it, its slots' bodies and the destructors in the link without
// a constructor. Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char wasmlogd_vt[] __asm__("_ZTVN9simulador9CWasmLogdE");
}

namespace {

const void* volatile wasmlogd_sink;

struct SWasmLogdRoots {
    SWasmLogdRoots() { wasmlogd_sink = wasmlogd_vt; }
} wasmlogd_roots;

} // namespace
