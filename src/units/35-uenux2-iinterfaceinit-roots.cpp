// Roots: keep comum::IInterfaceInit's members in the skeleton link the way the target reaches them. ~IInterfaceInit
// (target fn 5898) is reached through slot 0 of the IInterfaceInit and simulador::CWasmInit vtables and from CWasmInit's
// deleting destructor (fn 9388), none of them reconstructed yet; it is address-taken from a static constructor (body
// intact, `this` result kept as a table entry keeps it), which also brings in the vtable its vptr store names, and with
// it CurrentBootDevice (fn 11646, slot 2). The others are called directly in the target, by functions not reconstructed
// yet (ledger/callgraph.tsv: 2863 from 7160 and 12134, 2862 from 7160 12031 12134, 5897 and 3832 from 7160 and 12134,
// 729 from 17 functions): two noinline callers with different bodies give each two call sites, so binaryen keeps it out
// of line. DesabilitarMR has one call site, the one binaryen inlines it into in the target (7160).
// Declared through asm labels with the object's signatures (a destructor returns `this`); compiled with APP_CXXFLAGS,
// like the other stand-ins.
extern "C" {
int w5898_root_0(int) __asm__("_ZN5comum14IInterfaceInitD2Ev");
void w2863_root_0(int) __asm__("_ZN5comum14IInterfaceInit11HabilitarMREv");
void wDesabilitarMR_root_0(int) __asm__("_ZN5comum14IInterfaceInit13DesabilitarMREv");
int w2862_root_0(int) __asm__("_ZN5comum14IInterfaceInit24IsMRPresenteSemHabilitarEv");
int w5897_root_0(int) __asm__("_ZN5comum14IInterfaceInit23IsMRMontadoSemHabilitarEv");
void w3832_root_0(int) __asm__("_ZN5comum14IInterfaceInit25DesmontarMRSemDesabilitarEv");
int w729_root_0(int) __asm__("_ZN5comum14IInterfaceInit11GetDemoModeEv");
}

namespace {

__attribute__((noinline)) int PreparaMR(int init)
{
    w2863_root_0(init);
    if (!w2862_root_0(init))
        return 0;
    w2863_root_0(init);
    if (w5897_root_0(init)) {
        w3832_root_0(init);
        wDesabilitarMR_root_0(init);
    }
    return w729_root_0(init);
}

__attribute__((noinline)) int VerificaMR(int init, int vezes)
{
    if (w729_root_0(init))
        return vezes;
    w2863_root_0(init);
    if (w2862_root_0(init) && w5897_root_0(init))
        w3832_root_0(init);
    return vezes + 1;
}

void* volatile w5898_sink;

struct SW5898Roots {
    SW5898Roots()
    {
        w5898_sink = reinterpret_cast<void*>(&w5898_root_0);
        w5898_sink = reinterpret_cast<void*>(&PreparaMR);
        w5898_sink = reinterpret_cast<void*>(&VerificaMR);
    }
} w5898_roots;

} // namespace
