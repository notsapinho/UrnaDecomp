// Roots: keep vota::impl::CInformacaoThreadOperador's vtable in the skeleton link the way the target keeps it. Nothing
// calls the destructors (target fns 10552 and 10551) or the members of cinformacaothreadoperador.cpp directly: the
// target reaches them only through the vtable (@1590108, slots 0 to 30), whose address the constructor inlined into
// IInformacaoThreadOperador::GetInst (fn 599, not reconstructed) stores. Rooting the vtable keeps it, its slots'
// bodies and the destructors in the link without a constructor. Declared through an asm label, so this TU needs no
// uenux2 header and instantiates nothing.
extern "C" {
extern const char informacaothreadoperador_vt[] __asm__("_ZTVN4vota4impl25CInformacaoThreadOperadorE");
}

namespace {

const void* volatile informacaothreadoperador_sink;

struct SInformacaoThreadOperadorRoots {
    SInformacaoThreadOperadorRoots() { informacaothreadoperador_sink = informacaothreadoperador_vt; }
} informacaothreadoperador_roots;

} // namespace
