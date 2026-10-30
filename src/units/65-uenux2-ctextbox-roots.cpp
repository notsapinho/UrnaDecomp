// Roots: keep api::CTextBox's members (target fns 10957 Move, 10955 and 10954 the destructors, 10953 GetTypeName, and
// the pending Draw 10958 and Rect 10956) in the skeleton link the way the target keeps them. In the target the vtable
// (@1582232) is referenced by the constructor, inlined with std::make_shared<CTextBox> into fn 11805, not
// reconstructed, and by 10955 and 10954, reached only through it; its slots put every member in the table, and no
// target function calls one directly (ledger/callgraph.tsv has no caller of 10953 to 10958). Rooting the vtable keeps
// the same set. Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char ctextbox_vt[] __asm__("_ZTVN3api8CTextBoxE");
}

namespace {

const void* volatile ctextbox_sink;

struct SCTextBoxRoots {
    SCTextBoxRoots() { ctextbox_sink = ctextbox_vt; }
} ctextbox_roots;

} // namespace
