// Roots: keep comum::impl::CValidaMidia's vtable (@1577024) in the skeleton link the way the target reaches its slots:
// only through it, with no direct caller (ledger/callgraph.tsv has no edge into fns 11166 to 11173). The one function
// that stores its vptr, IValidaMidia::GetInst (fn 5575, `grep -rlE 'i32\.const 1577032($|[^0-9])'
// build/out/splat/pieces/asm`), is not reconstructed, so a static constructor takes the vtable's address in its place.
// Compiled as app code.
extern "C" {
extern const char cvalidamidia_vt[] __asm__("_ZTVN5comum4impl12CValidaMidiaE");
}

namespace {

const void* volatile cvalidamidia_sink;

struct SCValidaMidiaRoots {
    SCValidaMidiaRoots()
    {
        cvalidamidia_sink = cvalidamidia_vt;
    }
} cvalidamidia_roots;

} // namespace
