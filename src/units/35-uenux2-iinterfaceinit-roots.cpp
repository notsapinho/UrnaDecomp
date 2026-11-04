// Roots: keep comum::IInterfaceInit's members in the skeleton link the way the target reaches them. ~IInterfaceInit
// (target fn 5898) is reached through slot 0 of the IInterfaceInit and simulador::CWasmInit vtables and from CWasmInit's
// deleting destructor (fn 9388), which unit 127 writes: they keep it (body intact, `this` result kept as a table entry
// keeps it) with the vtable its vptr store names, and with it CurrentBootDevice (fn 11646, slot 2), so it takes nothing
// here. The others are called directly in the target (ledger/callgraph.tsv: 2863 from 7160 and 12134, 2862 from 7160
// and 12134 (12031 is in the link), 5897, 3832 and 5896 from 7160 and 12134, 729 from 17 functions), and of those
// callers 7160 is in the link (vota::CAjusteInicial::StartState, unit 329): VerificaMR, a noinline caller, stands for
// 12134 and gives each its second call site, so binaryen keeps it out of line. DesabilitarMR has one call site, 7160's,
// the one binaryen inlines it into in the target and in our link. DesligarUrna (fn
// 5894) takes nothing here: both its target callers, 11982 (unit 169) and 12017 (unit 61), are in the link.
// Declared through asm labels with the object's signatures (a destructor returns `this`); compiled with APP_CXXFLAGS,
// like the other stand-ins.
extern "C" {
void w2863_root_0(int) __asm__("_ZN5comum14IInterfaceInit11HabilitarMREv");
int w2862_root_0(int) __asm__("_ZN5comum14IInterfaceInit24IsMRPresenteSemHabilitarEv");
int w5897_root_0(int) __asm__("_ZN5comum14IInterfaceInit23IsMRMontadoSemHabilitarEv");
void w3832_root_0(int) __asm__("_ZN5comum14IInterfaceInit25DesmontarMRSemDesabilitarEv");
void w5896_root_0(int) __asm__("_ZN5comum14IInterfaceInit20MontarMRSemHabilitarEv");
int w729_root_0(int) __asm__("_ZN5comum14IInterfaceInit11GetDemoModeEv");
}

namespace {

__attribute__((noinline)) int VerificaMR(int init, int vezes)
{
    if (w729_root_0(init))
        return vezes;
    w2863_root_0(init);
    if (w2862_root_0(init) && w5897_root_0(init))
        w3832_root_0(init);
    else
        w5896_root_0(init);
    return vezes + 1;
}

void* volatile w5898_sink;

struct SW5898Roots {
    SW5898Roots()
    {
        w5898_sink = reinterpret_cast<void*>(&VerificaMR);
    }
} w5898_roots;

} // namespace
