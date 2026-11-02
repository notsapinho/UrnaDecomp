// Roots: reach comum::impl::IValidaMidia::GetInst (fn 5575) the way the target does until its caller lands. Its one
// caller, fn 12134, calls it twice (ledger/callgraph.tsv) and is not reconstructed; w179_usa stands for it with two call
// sites, so binaryen keeps GetInst out of line, and has a body no target function has. GetInst stores
// comum::impl::CValidaMidia's vptr (its constructor, inlined), which keeps the vtable and the slots the target reaches
// only through it. Compiled as app code; GetInst is declared through its mangled name.
extern "C" {
int w179_getinst() __asm__("_ZN5comum4impl12IValidaMidia7GetInstEv");
}

namespace {

__attribute__((noinline)) int w179_usa()
{
    return w179_getinst() == w179_getinst() ? 17 : 19;
}

int (*volatile w179_sink)();

struct SCValidaMidiaRoots {
    SCValidaMidiaRoots()
    {
        w179_sink = w179_usa;
    }
} w179_roots;

} // namespace
