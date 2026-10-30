// Roots: keep vota::CProgressoEncerramento's destructors (target fns 3907 and 12104, slots 0 and 1 of its vtable
// @1540588) in the skeleton link the way the target keeps them. In the target the vtable is referenced only by the
// constructor, which binaryen inlined into its one caller (fn 12098, CGravaResultado::StartState, through
// std::make_shared), not reconstructed yet; the vtable's slots put both destructors in the table, and the deleting
// destructor calls the other one. Rooting the vtable keeps the same set. The base-object destructor's second direct
// caller in the target, __shared_ptr_emplace<CProgressoEncerramento>::__on_zero_shared (fn 12085, libc++), exists only
// where std::make_shared<CProgressoEncerramento> is called, which needs the constructor; it is not stood in for: the
// destructor is in the table, so binaryen keeps it out of line with the one caller our link gives it. Declared through
// an asm label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char cprogressoencerramento_vt[] __asm__("_ZTVN4vota22CProgressoEncerramentoE");
}

namespace {

const void* volatile cprogressoencerramento_sink;

struct SCProgressoEncerramentoRoots {
    SCProgressoEncerramentoRoots() { cprogressoencerramento_sink = cprogressoencerramento_vt; }
} cprogressoencerramento_roots;

} // namespace
