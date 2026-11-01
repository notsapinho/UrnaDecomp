// Roots: keep api::CTextFieldBlinking's vtable in the skeleton link the way the target keeps it. Nothing calls the
// destructors (target fns 10942 and 10941) directly (ledger/callgraph.tsv has no edge into either): the target reaches
// them only through the vtable (@1582448, slots 0 and 1), whose address the constructor stores, and binaryen inlined
// the constructor into its one caller (fn 1265, unit 31's AddBlinkingTextField). Rooting the vtable keeps it, its slots' bodies and
// the destructors in the link without a constructor. Declared through an asm label, so this TU needs no uenux2 header
// and instantiates nothing.
extern "C" {
extern const char ctextfieldblinking_vt[] __asm__("_ZTVN3api18CTextFieldBlinkingE");
}

namespace {

const void* volatile ctextfieldblinking_sink;

struct SCTextFieldBlinkingRoots {
    SCTextFieldBlinkingRoots() { ctextfieldblinking_sink = ctextfieldblinking_vt; }
} ctextfieldblinking_roots;

} // namespace
