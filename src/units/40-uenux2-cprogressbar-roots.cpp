// Roots: keep api::CProgressBar's destructors (target fns 5509 and 10978, slots 0 and 1 of its vtable @1581760),
// GetTypeName (10975, slot 7) and Rect (10974, slot 8) in the skeleton link the way the target keeps them. In the
// target the vtable is referenced only by the constructor, which binaryen inlined into std::make_shared's fn 5545
// (called from fns 7787 and 12098, not reconstructed yet); the vtable's slots put every member in the table, and the
// deleting destructor calls the base-object one. The base-object destructor's other caller in the target is the
// virtual call of __shared_ptr_emplace<CProgressBar>::__on_zero_shared (fn 411, binaryen's one body for 44 such
// control blocks, through slot 0), so the deleting destructor is its only direct caller there too. Rooting the vtable
// keeps the same set. Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char cprogressbar_vt[] __asm__("_ZTVN3api12CProgressBarE");
}

namespace {

const void* volatile cprogressbar_sink;

struct SCProgressBarRoots {
    SCProgressBarRoots() { cprogressbar_sink = cprogressbar_vt; }
} cprogressbar_roots;

} // namespace
