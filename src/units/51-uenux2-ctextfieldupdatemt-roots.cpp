// Roots: keep api::CTextFieldUpdateMT's destructors and members (target fns 5411 and 10549, slots 0 and 1 of the
// vtable @1590476; Show 10546 and Hide 10545, slots 3 and 4) in the skeleton link the way the target keeps them. In
// the target the vtable is referenced by the constructor, which binaryen inlined into its one caller, fn 652 (not
// reconstructed; the constructor calls api::ITimerScheduler::GetInst, fn 1259); the vtable's slots put every member in
// the table, and the deleting destructor is the base-object one's only direct caller (awk -F'\t' '$2==5411'
// ledger/callgraph.tsv prints 10549). Taking the vtable's address keeps the same set. Declared through an asm label, so
// this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char ctextfieldupdatemt_vt[] __asm__("_ZTVN3api18CTextFieldUpdateMTE");
}

namespace {

const void* volatile ctextfieldupdatemt_sink;

struct SCTextFieldUpdateMTRoots {
    SCTextFieldUpdateMTRoots() { ctextfieldupdatemt_sink = ctextfieldupdatemt_vt; }
} ctextfieldupdatemt_roots;

} // namespace
