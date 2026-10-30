// Roots: keep simulador::CWasmImageSurfaceOps's and simulador::CWasmScreen's vtables in the skeleton link the way the
// target keeps them. The target reaches the slots of both through their vtables (@1528980, table entries 584 to 601;
// @1528816, entries 545 to 583), whose addresses the CWasmScreen constructor inlined into fn 8302 stores. That constructor
// is written in cwasmscreen.cpp, but nothing reconstructed calls it yet, so the link drops it; rooting the vtables keeps
// them and their slots' bodies. The only direct calls into these classes are 9058's and 9079's of slot 12 (fn 3493),
// pending. Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char wasmimagesurfaceops_vt[] __asm__("_ZTVN9simulador20CWasmImageSurfaceOpsE");
extern const char wasmscreen_vt[] __asm__("_ZTVN9simulador11CWasmScreenE");
}

namespace {

const void* volatile wasmimagesurfaceops_sink;
const void* volatile wasmscreen_sink;

struct SWasmImageSurfaceOpsRoots {
    SWasmImageSurfaceOpsRoots()
    {
        wasmimagesurfaceops_sink = wasmimagesurfaceops_vt;
        wasmscreen_sink = wasmscreen_vt;
    }
} wasmimagesurfaceops_roots;

} // namespace
