// Roots: keep simulador::CWasmImageSurfaceOps's vtable in the skeleton link the way the target keeps it. Only fn 3493
// (slot 12) has direct callers (ledger/callgraph.tsv: 9058 and 9079, simulador::CWasmScreen's members, not
// reconstructed); the target reaches every other slot through the vtable (@1528980, table entries 584 to 601), whose
// address the CWasmScreen constructor inlined into fn 8302 stores, its member at +44 being one of these. Rooting the
// vtable keeps it and its slots' bodies in the link without that constructor. Declared through an asm label, so this
// TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char wasmimagesurfaceops_vt[] __asm__("_ZTVN9simulador20CWasmImageSurfaceOpsE");
}

namespace {

const void* volatile wasmimagesurfaceops_sink;

struct SWasmImageSurfaceOpsRoots {
    SWasmImageSurfaceOpsRoots() { wasmimagesurfaceops_sink = wasmimagesurfaceops_vt; }
} wasmimagesurfaceops_roots;

} // namespace
