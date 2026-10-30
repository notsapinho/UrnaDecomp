// Roots: keep api::CMovieField's destructors (target fns 5524 and 11065, slots 0 and 1 of the vtable @1579432) and Hide
// (fn 11060, slot 4) in the skeleton link the way the target keeps them. In the target the vtable is referenced by the
// constructor, inlined with std::make_shared<CMovieField> into fn 5543 (callers 1593 and 3076), none of them
// reconstructed; the vtable's slots put the destructors and Hide in the table, and the deleting destructor is the
// base-object one's only direct caller (awk -F'\t' '$2==5524' ledger/callgraph.tsv prints 11065). Taking the vtable's
// address keeps the same set. Declared through an asm label, so this TU needs no uenux2 header and instantiates
// nothing.
extern "C" {
extern const char cmoviefield_vt[] __asm__("_ZTVN3api11CMovieFieldE");
}

namespace {

const void* volatile cmoviefield_sink;

struct SCMovieFieldRoots {
    SCMovieFieldRoots() { cmoviefield_sink = cmoviefield_vt; }
} cmoviefield_roots;

} // namespace
