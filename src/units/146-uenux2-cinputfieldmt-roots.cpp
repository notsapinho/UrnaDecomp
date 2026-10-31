// Roots: keep api::CInputFieldMT's vtable (@1587484), and with it Draw (target fn 10726, slot 2), in the skeleton link
// the way the target keeps it. In the target the vtable's one user is fn 1151, which builds the field and stores its vptr,
// and which is not reconstructed; the target reaches Draw only through that vtable (no direct caller in
// ledger/callgraph.tsv). Taking the vtable's address is that reference. Declared through an asm label, so this TU needs
// no uenux2 header and instantiates nothing.
extern "C" {
extern const char cinputfieldmt_vt[] __asm__("_ZTVN3api13CInputFieldMTE");
}

namespace {

const void* volatile cinputfieldmt_sink;

struct SCInputFieldMTRoots {
    SCInputFieldMTRoots() { cinputfieldmt_sink = cinputfieldmt_vt; }
} cinputfieldmt_roots;

} // namespace
