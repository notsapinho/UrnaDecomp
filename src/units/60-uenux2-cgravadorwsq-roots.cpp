// Roots: keep comum::CGravadorWSQ in the skeleton link the way the target keeps it. Its one user,
// vota::CGravaResultado::StartState (fn 12098), is not reconstructed yet:
// - 12098 calls the constructor (fn 3796, which stores the vptr @1557300, vtable @1557292) and hands the object to a
//   std::shared_ptr<IGravador>, whose deleter (fn 12092) inlines the destructor. The destructors (fns 11576, 11575,
//   slots 0 and 1) have no direct caller (awk -F'\t' '$2==11576 || $2==11575' ledger/callgraph.tsv prints nothing),
//   and the D0 inlines the D2. Taking the vtable's address keeps the same set: both in the table, no call.
// - the D2's store of IResultado's vptr (@1541028) keeps IResultado's vtable, and with it IResultado's destructor (fn
//   12090), which the target reaches only through the table too (slot 0 of IResultado's, IGravador's and
//   CGravadorRCSecao's vtables).
// Declared through an asm label, so this TU needs no uenux2 header.
extern "C" {
extern const char gravadorwsq_vt[] __asm__("_ZTVN5comum12CGravadorWSQE");
}

namespace {

const void* volatile gravadorwsq_sink;

struct SGravadorWSQRoots {
    SGravadorWSQRoots() { gravadorwsq_sink = gravadorwsq_vt; }
} gravadorwsq_roots;

} // namespace
