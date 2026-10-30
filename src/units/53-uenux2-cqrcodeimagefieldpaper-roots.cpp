// Roots: keep api::CQRCodeImageFieldPaper's vtable in the skeleton link the way the target keeps it. Nothing calls the
// destructors (target fns 10962 and 10961) directly (ledger/callgraph.tsv has no edge into either): the target reaches
// them only through the vtable (@1582072, slots 0 and 1), whose address the constructor inlined into fn 2775 (not
// reconstructed) stores. Rooting the vtable keeps it, its slots' bodies and the destructors in the link without a
// constructor. Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char qrcodeimagefieldpaper_vt[] __asm__("_ZTVN3api22CQRCodeImageFieldPaperE");
}

namespace {

const void* volatile qrcodeimagefieldpaper_sink;

struct SQRCodeImageFieldPaperRoots {
    SQRCodeImageFieldPaperRoots() { qrcodeimagefieldpaper_sink = qrcodeimagefieldpaper_vt; }
} qrcodeimagefieldpaper_roots;

} // namespace
