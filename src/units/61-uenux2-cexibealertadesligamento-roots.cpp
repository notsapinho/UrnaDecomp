// Roots: keep vota::CExibeAlertaDesligamento's destructors (target fns 2883 and 12019, slots 0 and 1 of its vtable
// @1543004) in the skeleton link the way the target keeps them.
//
// The vtable is referenced in the target only by the constructor, inlined into GetInst (fn 5979, not reconstructed),
// which with the static std::unique_ptr's exit-time destructor (fn 12022) also calls fn 2883 directly. Rooting the
// vtable keeps both destructors in the table, and the deleting destructor calls the other one; those two direct callers
// are not stood in for: the destructor is in the table, so binaryen keeps it out of line with the one caller our link
// gives it.
//
// Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cexibealertadesligamento_vt[] __asm__("_ZTVN4vota24CExibeAlertaDesligamentoE");
}

namespace {

const void* volatile cexibealertadesligamento_sink;

struct SCExibeAlertaDesligamentoRoots {
    SCExibeAlertaDesligamentoRoots()
    {
        cexibealertadesligamento_sink = cexibealertadesligamento_vt;
    }
} cexibealertadesligamento_roots;

} // namespace
