// Roots: keep unit 18's api::CThread members in the skeleton link, reached the way the target reaches them.
// - ~CThread (target fn 2721): the target reaches it through slot 0 of the CThread vtable and from the destructors of
//   CThreadVota, CThreadEleitor and CThreadOperador (fns 2126, 2438, 2717), none of them reconstructed yet; it is
//   address-taken from a static constructor (body intact, `this` result kept as a table entry keeps it), which also
//   brings in the vtable its vptr store names.
// - Start (target fn 1684): the target calls it directly, seven times from three slots of vota::CExecucaoVota (fns
//   10233, 10235, 10236; ledger/callgraph.tsv), none reconstructed yet and none through the table. Two noinline
//   callers give it more than one call site, so binaryen keeps its body out of line as the target does. Its thread
//   routine (fn 10255) needs no root: Start passes its address to IThreadImpl::Create, as the target does (elem[4527]).
// The callers are address-taken from a static constructor. Declared through asm labels with the wasm-level signatures;
// compiled as uenux2 code.
extern "C" {
int w2721_root_0(int) __asm__("_ZN3api7CThreadD2Ev");
void w1684_root_0(int) __asm__("_ZN3api7CThread5StartEv");
}

namespace {

__attribute__((noinline)) void IniciaThread(int thread)
{
    w1684_root_0(thread);
}

__attribute__((noinline)) void IniciaThreads(int primeira, int segunda, int terceira)
{
    w1684_root_0(primeira);
    w1684_root_0(segunda);
    w1684_root_0(terceira);
}

void* volatile w18_sink;

struct SW18Roots {
    SW18Roots()
    {
        w18_sink = reinterpret_cast<void*>(&w2721_root_0);
        w18_sink = reinterpret_cast<void*>(&IniciaThread);
        w18_sink = reinterpret_cast<void*>(&IniciaThreads);
    }
} w18_roots;

} // namespace
