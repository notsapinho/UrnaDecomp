// Roots: keep api::CDSImageField in the skeleton link the way the target keeps it. Its only constructor call is
// inlined into fn 502, not reconstructed yet, which allocates the field with operator new, stores its two vptrs
// (@1578868 and @1578920, of the vtables @1578860 and @1578912) and hands it to a std::shared_ptr whose control block
// deletes it through the vtable. So the destructors are reached through the vtable slots: the D2 (fn 2778) through slot
// 0 and from its three direct callers, the D0 (fn 11095) and the thunks at -44 (fns 11096, 11094; awk -F'\t'
// '$2==2778' ledger/callgraph.tsv prints the three), all of which the vtables hold. Taking the primary vtable's address
// keeps the same set: the vtable group holds both vtables, and with them every slot.
// Declared through an asm label, so this TU needs no uenux2 header.
extern "C" {
extern const char dsimagefield_vt[] __asm__("_ZTVN3api13CDSImageFieldE");
}

namespace {

const void* volatile dsimagefield_sink;

struct SDSImageFieldRoots {
    SDSImageFieldRoots() { dsimagefield_sink = dsimagefield_vt; }
} dsimagefield_roots;

} // namespace
