// Roots: keep the vtables of the zeresima states of src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk, and with
// them their slots (target fns 2879, 11984, 11983, 5961, 5960, 5964, 5963, 11939, 11845, 5958 and the pending traps),
// in the skeleton link the way the target keeps them.
//
// Each vtable is referenced in the target only by its class's constructor, inlined into the function that creates the
// singleton (fns 11931, 5962, 6056 and 5959, none reconstructed). Taking the vtables' addresses keeps every slot. The
// bases' vtables need no root: their destructors (fns 1720 and 1952), which the derived classes' destructors call,
// store them.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cinformacaozeresimatardia_vt[] __asm__("_ZTVN4vota25CInformacaoZeresimaTardiaE");
extern const char cgeraresumozeresima_vt[] __asm__("_ZTVN4vota19CGeraResumoZeresimaE");
extern const char cgerazeresima_vt[] __asm__("_ZTVN4vota13CGeraZeresimaE");
extern const char cconfirmaimpressaozeresima_vt[] __asm__("_ZTVN4vota26CConfirmaImpressaoZeresimaE");
extern const char cregeraresumozeresima_vt[] __asm__("_ZTVN4vota21CRegeraResumoZeresimaE");
}

namespace {

const void* volatile zeresima_sink;

struct SZeresimaRoots {
    SZeresimaRoots()
    {
        zeresima_sink = cinformacaozeresimatardia_vt;
        zeresima_sink = cgeraresumozeresima_vt;
        zeresima_sink = cgerazeresima_vt;
        zeresima_sink = cconfirmaimpressaozeresima_vt;
        zeresima_sink = cregeraresumozeresima_vt;
    }
} zeresima_roots;

} // namespace
