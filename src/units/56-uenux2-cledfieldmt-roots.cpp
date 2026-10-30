// Roots: keep api::CLedFieldMT in the skeleton link the way the target keeps it. Its users are not reconstructed yet:
// the factory body 3890 that 435's 33 callers reach (ledger/callgraph.tsv) news the field and stores its vptr (@1579692,
// vtable @1579684), and the forms reach Draw (fn 11050) and the destructors only through the vtable's slots (Draw is
// table[3276], no direct caller). Taking the vtable's address keeps the same set: every slot in the table, no direct
// call. Declared through an asm label, so this TU needs no uenux2 header.
extern "C" {
extern const char ledfieldmt_vt[] __asm__("_ZTVN3api11CLedFieldMTE");
}

namespace {

const void* volatile ledfieldmt_sink;

struct SLedFieldMTRoots {
    SLedFieldMTRoots() { ledfieldmt_sink = ledfieldmt_vt; }
} ledfieldmt_roots;

} // namespace
