// Roots: keep api::CImageFieldUpdate's destructors (target fns 5531 and 11086, slots 0 and 1 of its vtable @1578980) in
// the skeleton link the way the target keeps them. In the target the vtable is referenced by the constructor, which
// binaryen inlined into fn 3059 (not reconstructed), and by the base-object destructor itself; the vtable's slots put
// both destructors in the table, and the deleting destructor is the base-object one's only direct caller
// (awk -F'\t' '$2==5531' ledger/callgraph.tsv prints 11086). Taking the vtable's address keeps the same set. Declared
// through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char cimagefieldupdate_vt[] __asm__("_ZTVN3api17CImageFieldUpdateE");
}

namespace {

const void* volatile cimagefieldupdate_sink;

struct SCImageFieldUpdateRoots {
    SCImageFieldUpdateRoots() { cimagefieldupdate_sink = cimagefieldupdate_vt; }
} cimagefieldupdate_roots;

} // namespace
