// Roots: keep comum::CAssinador::~CAssinador (target fn 1007) in the skeleton link the way the target reaches it:
// through slot 0 of the CAssinador vtable, and from ten direct callers (491 1836 3333 4657 4668 4694 7174 7766 10590
// 12098, ledger/callgraph.tsv). Of those the deleting destructor (4694, slot 1), which comes with the vtable that the
// destructor's vptr store names, vota::CAssinadorVota's destructor (7766, fragment 165) and vota::CSincronizaVota's
// SincronizaRelatorios, GravaBancoDadosMI, AssinaRDVEBancoDados, SincronizaEstadoGeralVota and SincronizaEstadoGeral
// (1836, 4657, 4668, 491, 3333, fragment 205) are reconstructed, and so is 10590 (unit 283), which holds
// SincronizaJustificativa's signing inlined, and 7174 (unit 241), which holds two calls through the
// vota::CSincronizaVota members binaryen inlines into it. The noinline caller below stands in for the last, 12098; it is
// address-taken from a static constructor.
// Declared through an asm label with the wasm-level signature (a non-deleting destructor returns `this`); compiled
// with APP_CXXFLAGS.
extern "C" {
int w1007_root_0(int) __asm__("_ZN5comum10CAssinadorD2Ev");
}

namespace {

__attribute__((noinline)) void DestroiAssinadorA(int assinador)
{
    w1007_root_0(assinador);
}

// It drops the destructor's result: a stand-in that only returns it is vota::CAssinadorVota's destructor (fn 7766, a
// thunk into 1007) byte for byte, and the census and the splat scan pair it with that function.

void* volatile w1007_sink;

struct SW1007Roots {
    SW1007Roots()
    {
        w1007_sink = reinterpret_cast<void*>(&DestroiAssinadorA);
    }
} w1007_roots;

} // namespace
