// Roots: keep api::CTextFieldUpdate's destructors (target fns 5495 and 10917, slots 0 and 1 of the vtable @1582988) in
// the skeleton link the way the target keeps them. In the target the vtable is referenced by the constructor (fn 3658,
// not reconstructed: it calls api::ITimerScheduler::GetInst, fn 1259), which the make_shared callers 502, 3058 and 5936
// call; the vtable's slots put both destructors in the table, and the deleting destructor is the base-object one's only
// direct caller (awk -F'\t' '$2==5495' ledger/callgraph.tsv prints 10917). Taking the vtable's address keeps the same
// set. Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char ctextfieldupdate_vt[] __asm__("_ZTVN3api16CTextFieldUpdateE");
}

namespace {

const void* volatile ctextfieldupdate_sink;

struct SCTextFieldUpdateRoots {
    SCTextFieldUpdateRoots() { ctextfieldupdate_sink = ctextfieldupdate_vt; }
} ctextfieldupdate_roots;

} // namespace
