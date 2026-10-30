// Roots: keep vota::IQRCodeBUDS's destructors (target fns 12050, 12049) in the skeleton link the way the target reaches
// them: only through slots 0 and 1 of the class's vtable (@1542084; elem[1510] and elem[1511] are their only table
// entries), with no direct caller (ledger/callgraph.tsv lists them as callers only). Their users, GetQRDSInst (fn
// 1956, which builds the object) and the shared_ptr that deletes it, are not reconstructed yet. Taking the vtable's
// address from a static constructor keeps the same set: it puts both destructors in the table, as the target has them.
// Declared through an asm label, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
extern const char iqrcodebuds_vt[] __asm__("_ZTVN4vota11IQRCodeBUDSE");
}

namespace {

const void* volatile iqrcodebuds_sink;

struct SIQRCodeBUDSRoots {
    SIQRCodeBUDSRoots() { iqrcodebuds_sink = iqrcodebuds_vt; }
} iqrcodebuds_roots;

} // namespace
