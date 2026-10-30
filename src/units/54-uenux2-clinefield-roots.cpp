// Roots: keep api::CLineField's members (target fns 11066 GetTypeName, 11067 Rect, and the pending Draw 11068 and Move
// 5527, slots 7, 8, 2 and 9 of the CLineField vtable @1579356) in the skeleton link the way the target keeps them. In
// the target the vtable is referenced only by the constructor, which is inlined into the std::make_shared<CLineField>
// of fn 2244 (not reconstructed yet); the vtable's slots put every member in the table, and no target function calls
// one directly (ledger/callgraph.tsv has no caller of 11066, 11067 or 11068). Rooting the vtable keeps the same set.
// Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char clinefield_vt[] __asm__("_ZTVN3api10CLineFieldE");
}

namespace {

const void* volatile clinefield_sink;

struct SCLineFieldRoots {
    SCLineFieldRoots() { clinefield_sink = clinefield_vt; }
} clinefield_roots;

} // namespace
