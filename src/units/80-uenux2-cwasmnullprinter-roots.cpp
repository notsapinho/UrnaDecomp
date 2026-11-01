// Roots: keep unit 80's classes in the skeleton link, reached the way the target reaches them. The target creates its
// one CWasmNullPaper and CWasmNullPrinter in simulador's init (fn 8302, unit 188), which stores their vtables, so they
// need no line here. CCutFieldPaper's vptr is stored in fn 1264 and CNewLineFieldPaper's reaches fn 3890 through thunk
// 198, both written (unit 31). Every virtual member here is reached through those vtables only (`awk -F'\t' '$2==8365'
// ledger/callgraph.tsv` and the same for the other slots print nothing). So this file takes those two vtables'
// addresses, the reference the constructors' vptr stores give, which keeps every slot. The constructors of the error classes are not rooted: fn 10257 has its two callers in IImpressora's
// defaults, and the other two have one caller, SetStyle, into which binaryen inlines them as in the target. Declared
// through __asm__ labels, no header; compiled with APP_CXXFLAGS.
extern const char cutfieldpaper_vt[] __asm__("_ZTVN3api14CCutFieldPaperE");
extern const char newlinefieldpaper_vt[] __asm__("_ZTVN3api18CNewLineFieldPaperE");

namespace {

const void* volatile cwasmnullprinter_sink;

struct SCWasmNullPrinterRoots {
    SCWasmNullPrinterRoots()
    {
        cwasmnullprinter_sink = cutfieldpaper_vt;
        cwasmnullprinter_sink = newlinefieldpaper_vt;
    }
} cwasmnullprinter_roots;

} // namespace
