// Roots: keep comum::CMenuBase's destructors (target fns 12235, 6188) in the skeleton link the way the target reaches
// them: only through slots 0 and 1 of the class's vtable (@1550924; the base-object destructor's one table entry,
// elem[1357], is also slot 0 of vota::CMenuMaisInformacoesVota's), with no direct caller (ledger/callgraph.tsv has no
// edge into either). Their users, the constructor that binaryen inlined into fn 6599 (the builder of the
// "Mais informa\xE7\xF5es" menu) and that builder, are not reconstructed yet. Taking the vtable's address from a static
// constructor keeps the same set: it puts both destructors and slot 2 in the table, as the target has them. Declared
// through an asm label, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
extern const char cmenubase_vt[] __asm__("_ZTVN5comum9CMenuBaseE");
}

namespace {

const void* volatile cmenubase_sink;

struct SCMenuBaseRoots {
    SCMenuBaseRoots() { cmenubase_sink = cmenubase_vt; }
} cmenubase_roots;

} // namespace
